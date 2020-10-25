#include <fstream>
#include <string>
#include <cstdlib>
#include <tree_sitter/api.h>

extern "C" {
#include "javascript/src/parser.c"
#include "javascript/src/scanner.c"
}

#define LANGUAGE tree_sitter_javascript
#define SOURCE_PATH "javascript/examples/jquery.js"

int main() {
  TSParser *parser = ts_parser_new();
  if (!ts_parser_set_language(parser, LANGUAGE())) {
    fprintf(stderr, "Invalid language\n");
    exit(1);
  }

  const char *source_path = GRAMMARS_DIR SOURCE_PATH;

  printf("Parsing %s\n", source_path);

  std::ifstream source_file(source_path);
  if (!source_file.good()) {
    fprintf(stderr, "Invalid source path %s\n", source_path);
    exit(1);
  }

  std::string source_code(
    (std::istreambuf_iterator<char>(source_file)),
    std::istreambuf_iterator<char>()
  );

  TSTree *tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code.c_str(),
    source_code.size()
  );
}
