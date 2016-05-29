#include "spec_helper.h"
#include "helpers/load_language.h"
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <map>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "tree_sitter/compiler.h"

using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;

map<string, const TSLanguage *> loaded_languages;
int libcompiler_mtime = -1;

const char *libcompiler_path =
#if defined(__linux)
  "out/Test/obj.target/libcompiler.a";
#else
  "out/Test/libcompiler.a";
#endif

static std::string run_cmd(const char *cmd, const char *args[]) {
  int child_pid = fork();
  if (child_pid < 0)
    return "fork failed";

  if (child_pid == 0) {
    close(0);
    dup2(1, 0);
    dup2(2, 1);
    dup2(1, 2);
    execvp(cmd, (char * const * )args);
    return "";
  }

  int status;
  do {
    waitpid(child_pid, &status, 0);
  } while (!WIFEXITED(status));

  if (WEXITSTATUS(status) == 0)
    return "";
  else
    return "command failed";

  return "";
}

static int get_modified_time(const string &path) {
  struct stat file_stat;
  if (stat(path.c_str(), &file_stat) != 0) {
    if (errno != ENOENT)
      fprintf(stderr, "Error in stat() for path: %s\n", + path.c_str());
    return 0;
  }
  return file_stat.st_mtime;
}

const TSLanguage *load_language(const string &name, const string &code, int timestamp) {
  mkdir("out/tmp", 0777);

  string pwd(getenv("PWD"));
  string language_function_name = "ts_language_" + name;
  string header_dir = pwd + "/include";
  string source_filename = pwd + "/out/tmp/" + name + ".c";
  string obj_filename = source_filename + ".o";
  string lib_filename = source_filename + ".so";

  int lib_mtime = get_modified_time(lib_filename);
  int header_mtime = get_modified_time(header_dir + "/tree_sitter/parser.h");
  if (!timestamp || !header_mtime || lib_mtime < timestamp || lib_mtime < header_mtime) {
    ofstream source_file;
    source_file.open(source_filename);
    source_file << code;
    source_file.close();

    const char *compiler_name = getenv("CC");
    if (!compiler_name) {
      compiler_name = "gcc";
    }

    const char *compile_argv[] = {
      compiler_name,
      "-x", "c",
      "-fPIC",
      "-g",
      "-I", header_dir.c_str(),
      "-c", source_filename.c_str(),
      "-o", obj_filename.c_str(),
      NULL
    };
    string compile_error = run_cmd("gcc", compile_argv);
    if (!compile_error.empty()) {
      AssertThat(string(compile_error), IsEmpty());
      return nullptr;
    }

    const char *link_argv[] = {
      compiler_name,
      "-shared",
      "-Wl", obj_filename.c_str(),
      "-o", lib_filename.c_str(),
      NULL
    };
    string link_error = run_cmd("gcc", link_argv);
    if (!link_error.empty()) {
      AssertThat(link_error, IsEmpty());
      return nullptr;
    }
  }

  void *parser_lib = dlopen(lib_filename.c_str(), RTLD_NOW);
  if (!parser_lib) {
    std::string message(dlerror());
    AssertThat(message, IsEmpty());
    return nullptr;
  }

  void *symbol_value = dlsym(parser_lib, language_function_name.c_str());
  if (!symbol_value) {
    std::string message(dlerror());
    AssertThat(message, IsEmpty());
    return nullptr;
  }

  typedef TSLanguage * (* LanguageFunction)();
  LanguageFunction language_fn = reinterpret_cast<LanguageFunction>(symbol_value);
  return language_fn();
}

const TSLanguage *load_language(const string &name, const TSCompileResult &compile_result) {
  if (compile_result.error_type != TSCompileErrorTypeNone) {
    Assert::Failure(string("Compilation failed ") + compile_result.error_message);
    return nullptr;
  }

  const TSLanguage *language = load_language(name, compile_result.code, 0);
  free(compile_result.code);
  return language;
}

const TSLanguage *get_test_language(const string &language_name) {
  if (loaded_languages[language_name])
    return loaded_languages[language_name];

  if (libcompiler_mtime == -1) {
    libcompiler_mtime = get_modified_time(libcompiler_path);
    if (!libcompiler_mtime)
      return nullptr;
  }

  string language_dir = string("spec/fixtures/grammars/") + language_name;
  string grammar_filename = language_dir + "/src/grammar.json";
  string parser_filename = language_dir + "/src/parser.c";

  int grammar_mtime = get_modified_time(grammar_filename);
  if (!grammar_mtime)
    return nullptr;

  int parser_mtime = get_modified_time(parser_filename);

  int input_mtime = (grammar_mtime > libcompiler_mtime) ?
    grammar_mtime :
    libcompiler_mtime;

  string parser_code;
  if (!parser_mtime || parser_mtime < input_mtime) {
    printf("\n" "Regenerating the %s parser...\n", language_name.c_str());

    ifstream grammar_file(grammar_filename);
    istreambuf_iterator<char> grammar_file_iterator(grammar_file), end_iterator;
    std::string grammar_json(grammar_file_iterator, end_iterator);

    TSCompileResult result = ts_compile_grammar(grammar_json.c_str());
    if (result.error_type != TSCompileErrorTypeNone) {
      fprintf(stderr, "Failed to compile %s grammar: %s\n", language_name.c_str(), result.error_message);
      return nullptr;
    }

    ofstream parser_file(parser_filename);
    parser_file << result.code;
    parser_code = result.code;

    grammar_file.close();
    parser_file.close();
  } else {
    ifstream parser_file(parser_filename);
    istreambuf_iterator<char> grammar_file_iterator(parser_file), end_iterator;
    parser_code.assign(grammar_file_iterator, end_iterator);
  }

  const TSLanguage *language = load_language(language_name, parser_code, input_mtime);
  loaded_languages[language_name] = language;
  return language;
};
