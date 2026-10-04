#include "tree_sitter/parser.h"

enum TokenType { HEAD, TAIL };

void *tree_sitter_depends_on_column_repetition_external_scanner_create(void) { return NULL; }

void tree_sitter_depends_on_column_repetition_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_depends_on_column_repetition_external_scanner_serialize(
  void *payload, char *buffer
) {
  return 0;
}

void tree_sitter_depends_on_column_repetition_external_scanner_deserialize(
  void *payload, const char *buffer, unsigned length
) {}

bool tree_sitter_depends_on_column_repetition_external_scanner_scan(
  void *payload, TSLexer *lexer, const bool *valid_symbols
) {
  if (lexer->lookahead != 'x') return false;
  lexer->result_symbol = lexer->get_column(lexer) == 0 ? HEAD : TAIL;
  lexer->advance(lexer, false);
  return true;
}
