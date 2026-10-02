#include "tree_sitter/parser.h"

enum TokenType {
  IDENTIFIER,
};

void *tree_sitter_external_word_token_external_scanner_create(void) { return NULL; }

void tree_sitter_external_word_token_external_scanner_destroy(void *payload) {}

unsigned tree_sitter_external_word_token_external_scanner_serialize(void *payload, char *buffer) {
  return 0;
}

void tree_sitter_external_word_token_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

static bool is_word_char(int32_t c) { return c >= 'a' && c <= 'z'; }

bool tree_sitter_external_word_token_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  if (!valid_symbols[IDENTIFIER]) return false;

  while (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
         lexer->lookahead == '\r' || lexer->lookahead == '\n') {
    lexer->advance(lexer, true);
  }

  if (!is_word_char(lexer->lookahead)) return false;
  while (is_word_char(lexer->lookahead)) lexer->advance(lexer, false);
  lexer->result_symbol = IDENTIFIER;
  return true;
}
