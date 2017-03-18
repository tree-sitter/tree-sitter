#include "test_helper.h"
#include "helpers/load_language.h"
#include "helpers/file_helpers.h"
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "tree_sitter/compiler.h"

using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;

map<string, const TSLanguage *> loaded_languages;
int libcompiler_mtime = -1;
int compile_result_count = 0;

const char *libcompiler_path =
#if defined(__linux)
  "out/Test/obj.target/libcompiler.a";
#else
  "out/Test/libcompiler.a";
#endif

static std::string run_command(const char *cmd, const char *args[]) {
  int child_pid = fork();
  if (child_pid < 0) {
    return "fork failed";
  }

  if (child_pid == 0) {
    close(0);
    dup2(1, 0);
    dup2(2, 1);
    dup2(1, 2);
    execvp(cmd, (char * const * )args);
  }

  int status;
  do {
    waitpid(child_pid, &status, 0);
  } while (!WIFEXITED(status));

  if (WEXITSTATUS(status) == 0) {
    return "";
  } else {
    return "command failed";
  }
}

static const TSLanguage *load_language(const string &source_filename,
                                       const string &lib_filename,
                                       const string &language_name,
                                       string external_scanner_filename = "") {
  string language_function_name = "tree_sitter_" + language_name;
  string header_dir = getenv("PWD") + string("/include");
  int source_mtime = get_modified_time(source_filename);
  int header_mtime = get_modified_time(header_dir + "/tree_sitter/parser.h");
  int lib_mtime = get_modified_time(lib_filename);
  int external_scanner_mtime = get_modified_time(external_scanner_filename);

  if (!header_mtime || lib_mtime < header_mtime || lib_mtime < source_mtime ||
      lib_mtime < external_scanner_mtime) {
    const char *compiler_name = getenv("CXX");
    if (!compiler_name) compiler_name = "c++";

    vector<const char *> compile_args = {
      compiler_name,
      "-shared",
      "-fPIC",
      "-I", header_dir.c_str(),
      "-o", lib_filename.c_str(),
      "-x", "c",
      source_filename.c_str()
    };

    if (!external_scanner_filename.empty()) {
      compile_args.push_back("-g");
      string extension = external_scanner_filename.substr(external_scanner_filename.rfind("."));
      if (extension == ".c") {
        compile_args.push_back("-xc");
      } else {
        compile_args.push_back("-xc++");
      }
      compile_args.push_back(external_scanner_filename.c_str());
    }

    compile_args.push_back(nullptr);

    string compile_error = run_command(compiler_name, compile_args.data());
    if (!compile_error.empty()) {
      AssertThat(string(compile_error), IsEmpty());
      return nullptr;
    }
  }

  void *parser_lib = dlopen(lib_filename.c_str(), RTLD_NOW);
  if (!parser_lib) {
    std::string message(dlerror());
    AssertThat(message, IsEmpty());
    return nullptr;
  }

  void *language_function = dlsym(parser_lib, language_function_name.c_str());
  if (!language_function) {
    std::string message(dlerror());
    AssertThat(message, IsEmpty());
    return nullptr;
  }

  return reinterpret_cast<TSLanguage *(*)()>(language_function)();
}

const TSLanguage *load_test_language(const string &name,
                                     const TSCompileResult &compile_result,
                                     string external_scanner_path) {
  if (compile_result.error_type != TSCompileErrorTypeNone) {
    Assert::Failure(string("Compilation failed ") + compile_result.error_message);
    return nullptr;
  }

  mkdir("out/tmp", 0777);
  string source_filename = "out/tmp/compile-result-" + to_string(compile_result_count) + ".c";
  string lib_filename = source_filename + ".so";
  compile_result_count++;

  ofstream source_file;
  source_file.open(source_filename);
  source_file << compile_result.code;
  source_file.close();

  auto language = load_language(source_filename, lib_filename, name, external_scanner_path);
  free(compile_result.code);
  return language;
}

const TSLanguage *load_real_language(const string &language_name) {
  if (loaded_languages[language_name])
    return loaded_languages[language_name];

  string language_dir = string("test/fixtures/grammars/") + language_name;
  string grammar_filename = language_dir + "/src/grammar.json";
  string parser_filename = language_dir + "/src/parser.c";
  string external_scanner_filename = language_dir + "/src/scanner.cc";
  if (!file_exists(external_scanner_filename)) {
    external_scanner_filename = "";
  }

  int grammar_mtime = get_modified_time(grammar_filename);
  if (!grammar_mtime)
    return nullptr;

  if (libcompiler_mtime == -1) {
    libcompiler_mtime = get_modified_time(libcompiler_path);
    if (!libcompiler_mtime)
      return nullptr;
  }

  int parser_mtime = get_modified_time(parser_filename);

  if (parser_mtime <= grammar_mtime || parser_mtime <= libcompiler_mtime) {
    printf("\n" "Regenerating the %s parser...\n", language_name.c_str());

    string grammar_json = read_file(grammar_filename);
    TSCompileResult result = ts_compile_grammar(grammar_json.c_str());
    if (result.error_type != TSCompileErrorTypeNone) {
      fprintf(stderr, "Failed to compile %s grammar: %s\n", language_name.c_str(), result.error_message);
      return nullptr;
    }

    write_file(parser_filename, result.code);
  }

  mkdir("out/tmp", 0777);
  string lib_filename = "out/tmp/" + language_name + ".so";
  const TSLanguage *language = load_language(parser_filename, lib_filename, language_name, external_scanner_filename);
  loaded_languages[language_name] = language;
  return language;
};
