#include <tree_sitter/parser.h>

enum {
  COMMENT,
};

void *tree_sitter_external_extra_tokens_external_scanner_create() { return NULL; }

void tree_sitter_external_extra_tokens_external_scanner_destroy(void *payload) {}

void tree_sitter_external_extra_tokens_external_scanner_reset(void *payload) {}

bool tree_sitter_external_extra_tokens_external_scanner_serialize(void *payload, TSExternalTokenState state) { return true; }

void tree_sitter_external_extra_tokens_external_scanner_deserialize(void *payload, TSExternalTokenState state) {}

bool tree_sitter_external_extra_tokens_external_scanner_scan(
  void *payload, TSLexer *lexer, const bool *whitelist) {

  while (lexer->lookahead == ' ') {
    lexer->advance(lexer, true);
  }

  if (lexer->lookahead == '#') {
    lexer->advance(lexer, false);
    while (lexer->lookahead != '\n') {
      lexer->advance(lexer, false);
    }

    lexer->result_symbol = COMMENT;
    return true;
  }

  return false;
}

