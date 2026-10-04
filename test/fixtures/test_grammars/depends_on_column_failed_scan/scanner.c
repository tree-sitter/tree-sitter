#include "tree_sitter/parser.h"

enum TokenType { HEAD };

void *tree_sitter_depends_on_column_failed_scan_external_scanner_create(void) { return NULL; }

void tree_sitter_depends_on_column_failed_scan_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_depends_on_column_failed_scan_external_scanner_serialize(
  void *payload, char *buffer
) {
  return 0;
}

void tree_sitter_depends_on_column_failed_scan_external_scanner_deserialize(
  void *payload, const char *buffer, unsigned length
) {}

bool tree_sitter_depends_on_column_failed_scan_external_scanner_scan(
  void *payload, TSLexer *lexer, const bool *valid_symbols
) {
  if (lexer->lookahead != 'x' || lexer->get_column(lexer) != 0) return false;
  lexer->result_symbol = HEAD;
  lexer->advance(lexer, false);
  return true;
}
