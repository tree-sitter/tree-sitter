#include "helpers/test_languages.h"
#include "helpers/load_language.h"
#include <sys/stat.h>
#include <fstream>
#include <map>
#include <string>

using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;

map<string, const TSLanguage *> loaded_languages;
int libcompiler_mtime = -1;

const char libcompiler_path[] =
#if defined(__linux)
  "out/Test/obj.target/libcompiler.a"
#else
  "out/Test/libcompiler.a"
#endif
;

static int get_modified_time(const string &path) {
  struct stat file_stat;
  int error = stat(path.c_str(), &file_stat);
  if (error != 0) {
    fprintf(stderr, "Error in stat() for path: %s\n", + path.c_str());
    return 0;
  }

  return file_stat.st_mtime;
}

const TSLanguage *get_test_language(const string &language_name) {
  if (libcompiler_mtime == -1) {
    libcompiler_mtime = get_modified_time(libcompiler_path);
    if (!libcompiler_mtime) {
      return nullptr;
    }
  }

  if (loaded_languages[language_name]) {
    return loaded_languages[language_name];
  }

  string language_dir = string("spec/fixtures/") + language_name;
  string grammar_filename = language_dir + "/src/grammar.json";
  string parser_filename = language_dir + "/src/parser.c";

  int grammar_mtime = get_modified_time(grammar_filename);
  if (!grammar_mtime) {
    return nullptr;
  }

  int parser_mtime = get_modified_time(parser_filename);
  if (!parser_mtime) {
    return nullptr;
  }

  string parser_code;
  if (parser_mtime <= grammar_mtime || parser_mtime <= libcompiler_mtime) {
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

  const TSLanguage *language = load_language(language_name, parser_code);
  loaded_languages[language_name] = language;
  return language;
};
