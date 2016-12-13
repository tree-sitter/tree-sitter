#include <tree_sitter/parser.h>

enum {
  COMMENT,
};

void *ts_language_extra_external_tokens_external_scanner_create() {
  return NULL;
}

void ts_language_extra_external_tokens_external_scanner_destroy(void *payload) {
}

bool ts_language_extra_external_tokens_external_scanner_scan(
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
