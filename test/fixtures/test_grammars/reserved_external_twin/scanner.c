#include "tree_sitter/parser.h"

enum {
  K,
};

void *tree_sitter_reserved_external_twin_external_scanner_create() {
  return NULL;
}

void tree_sitter_reserved_external_twin_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_reserved_external_twin_external_scanner_serialize(
  void *payload,
  char *buffer
) { return 0; }

void tree_sitter_reserved_external_twin_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

bool tree_sitter_reserved_external_twin_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  // Where `k` is valid, `x` also spells it.
  if (!valid_symbols[K]) return false;

  while (lexer->lookahead == ' ' || lexer->lookahead == '\n') {
    lexer->advance(lexer, true);
  }

  if (lexer->lookahead != 'x') return false;

  lexer->advance(lexer, false);
  lexer->result_symbol = K;
  return true;
}
