#include "spec_helper.h"
#include "helpers/load_language.h"
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <fstream>
#include "tree_sitter/compiler.h"

using std::string;
using std::ofstream;

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

const TSLanguage *load_language(const string &name, const TSCompileResult &compile_result) {
  if (compile_result.error_type != TSCompileErrorTypeNone) {
    AssertThat(string(compile_result.error_message), IsEmpty());
    return nullptr;
  }

  return load_language(name, compile_result.code);
}

const TSLanguage *load_language(const string &name, const string &code) {
  string language_function_name = "ts_language_" + name;

  static char source_file_template[256] = {};
  snprintf(source_file_template, 256, "/tmp/tree-sitter-test-%sXXXXXXXXX", name.c_str());

  const char *temp_directory = mkdtemp(source_file_template);
  if (!temp_directory) {
    AssertThat(string("Failed to create temp directory"), IsEmpty());
    return nullptr;
  }

  string source_filename = string(temp_directory) + "/parser.c";
  string obj_filename = string(source_filename) + ".o";
  string lib_filename = string(source_filename) + ".so";
  string header_dir = string(getenv("PWD")) + "/include";

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
