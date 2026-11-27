#include "tree_sitter/parser.h"

enum TokenType { A, B };

void *tree_sitter_no_internal_tokens_external_scanner_create(void) { return NULL; }

void tree_sitter_no_internal_tokens_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_no_internal_tokens_external_scanner_serialize(void *payload, char *buffer) {
  return 0;
}

void tree_sitter_no_internal_tokens_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

bool tree_sitter_no_internal_tokens_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  if (lexer->lookahead == 'a' && valid_symbols[A]) {
    lexer->advance(lexer, false);
    lexer->result_symbol = A;
    return true;
  }
  if (lexer->lookahead == 'b' && valid_symbols[B]) {
    lexer->advance(lexer, false);
    lexer->result_symbol = B;
    return true;
  }
  return false;
}
