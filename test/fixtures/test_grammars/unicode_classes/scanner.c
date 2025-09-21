#include "tree_sitter/parser.h"

#include <wctype.h>

enum TokenType {
  LETTER_NUMBER_WITH_PREFIX,
};

void *tree_sitter_unicode_classes_external_scanner_create() { return NULL; }

void tree_sitter_unicode_classes_external_scanner_destroy(void *payload) { }

unsigned tree_sitter_unicode_classes_external_scanner_serialize(void *payload, char *buffer) { return 0; }

void tree_sitter_unicode_classes_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) { }

bool tree_sitter_unicode_classes_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  while (iswspace(lexer->lookahead)) {
    lexer->advance(lexer, false);
  }

  // If the letter number starts with a `!`, we've found the prefix, and can leverage
  // the new `matches` functions to consume the rest of the token without having to
  // duplicate the character set here.
  if (valid_symbols[LETTER_NUMBER_WITH_PREFIX] && lexer->lookahead == '!') {
    lexer->advance(lexer, false);
    if (matches_sym_letter_number(lexer->lookahead)) {
      lexer->advance(lexer, false);
      while (matches_sym_letter_number(lexer->lookahead)) {
        lexer->advance(lexer, false);
      }
      lexer->result_symbol = LETTER_NUMBER_WITH_PREFIX;
      return true;
    }
  }
}
