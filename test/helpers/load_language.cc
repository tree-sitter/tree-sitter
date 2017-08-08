#include "helpers/load_language.h"
#include "helpers/file_helpers.h"
#include <cassert>
#include <sys/types.h>
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
using std::vector;
using std::to_string;

map<string, const TSLanguage *> loaded_languages;
int libcompiler_mtime = -1;
int compile_result_count = 0;

#ifdef _WIN32

#include <windows.h>

const char *libcompiler_path = "test\\lib\\compiler.lib";
const char *dylib_extension = ".dll";

static string get_cwd() {
  string result(255, 0);
  result.resize(GetCurrentDirectory(result.size(), &result[0]));
  return result;
}

static int compile_parser(
  string source_filename,
  string scanner_source_filename,
  string output_filename,
  string header_dirname
) {
  CreateDirectory("out", nullptr);
  CreateDirectory("out\\tmp", nullptr);

  string command = "cl.exe";
  command += " /LD";
  command += " /I " + header_dirname;
  command += " " + source_filename;
  command += " " + scanner_source_filename;
  command += " /link /out:" + output_filename;
  return system(command.c_str());
}

static void *load_function_from_library(string library_path, string function_name) {
  HINSTANCE library = LoadLibrary(library_path.c_str());
  if (!library) {
    fputs(("Could not load library " + library_path).c_str(), stderr);
    abort();
  }

  void *function = static_cast<void *>(GetProcAddress(library, function_name.c_str()));
  if (!function) {
    fputs(("Could not find function + " + function_name).c_str(), stderr);
    abort();
  }

  return function;
}

#else // POSIX

#ifdef __linux

const char *libcompiler_path = "out/Test/obj.target/libcompiler.a";
const char *dylib_extension = ".so";

#else // macOS

const char *libcompiler_path = "out/Test/libcompiler.a";
const char *dylib_extension = ".dylib";

#endif

#include <unistd.h>
#include <dlfcn.h>

static string get_cwd() {
  return string(getenv("PWD"));
}

static int compile_parser(
  string source_filename,
  string scanner_source_filename,
  string output_filename,
  string header_dirname
) {
  mkdir("out", 0777);
  mkdir("out/tmp", 0777);

  const char *compiler_name = getenv("CXX");
  if (!compiler_name) compiler_name = "c++";

  string command = compiler_name;
  command += " -shared";
  command += " -fPIC ";
  command += " -I " + header_dirname;
  command += " -o " + output_filename;
  command += " -xc " + source_filename;

  if (!scanner_source_filename.empty()) {
    command += " -g";
    string extension = scanner_source_filename.substr(scanner_source_filename.rfind("."));
    if (extension == ".c") {
      command += " -xc " + scanner_source_filename;
    } else {
      command += " -xc++ " + scanner_source_filename;
    }
  }

  return system(command.c_str());
}

static void *load_function_from_library(string library_path, string function_name) {
  void *parser_lib = dlopen(library_path.c_str(), RTLD_NOW);
  if (!parser_lib) {
    fputs(dlerror(), stderr);
    abort();
  }

  void *language_function = dlsym(parser_lib, function_name.c_str());
  if (!language_function) {
    fputs(dlerror(), stderr);
    abort();
  }

  return language_function;
}

#endif

static const TSLanguage *load_language(const string &source_filename,
                                       const string &lib_filename,
                                       const string &language_name,
                                       string external_scanner_filename = "") {
  string language_function_name = "tree_sitter_" + language_name;
  string header_dir = join_path({get_cwd(), "include"});
  int source_mtime = get_modified_time(source_filename);
  int header_mtime = get_modified_time(join_path({header_dir, "tree_sitter", "parser.h"}));
  int lib_mtime = get_modified_time(lib_filename);
  int external_scanner_mtime = get_modified_time(external_scanner_filename);

  if (!header_mtime || lib_mtime < header_mtime || lib_mtime < source_mtime ||
      lib_mtime < external_scanner_mtime) {
    const char *compiler_name = getenv("CXX");
    if (!compiler_name) compiler_name = "c++";

    int status_code = compile_parser(
      source_filename,
      external_scanner_filename,
      lib_filename,
      header_dir
    );

    if (status_code != 0) abort();
  }

  void *language_function = load_function_from_library(lib_filename, language_function_name);

  return reinterpret_cast<TSLanguage *(*)()>(language_function)();
}

const TSLanguage *load_test_language(const string &name,
                                     const TSCompileResult &compile_result,
                                     string external_scanner_path) {
  if (compile_result.error_type != TSCompileErrorTypeNone) {
    fputs((string("Compilation failed ") + compile_result.error_message).c_str(), stderr);
    abort();
  }

  string source_filename = join_path({"out", "tmp", "compile-result-" + to_string(compile_result_count) + ".c"});
  string lib_filename = source_filename + dylib_extension;
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

  string language_dir = join_path({"test", "fixtures", "grammars", language_name});
  string grammar_filename = join_path({language_dir, "src", "grammar.json"});
  string parser_filename = join_path({language_dir, "src", "parser.c"});
  string external_scanner_filename = join_path({language_dir, "src", "scanner.cc"});
  if (!file_exists(external_scanner_filename)) {
    external_scanner_filename = join_path({language_dir, "src", "scanner.c"});
    if (!file_exists(external_scanner_filename)) {
      external_scanner_filename = "";
    }
  }

  int grammar_mtime = get_modified_time(grammar_filename);
  if (!grammar_mtime) return nullptr;

  if (libcompiler_mtime == -1) {
    libcompiler_mtime = get_modified_time(libcompiler_path);
    if (!libcompiler_mtime) return nullptr;
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

  string lib_filename = join_path({"out", "tmp", language_name + dylib_extension});
  const TSLanguage *language = load_language(parser_filename, lib_filename, language_name, external_scanner_filename);
  loaded_languages[language_name] = language;
  return language;
};
