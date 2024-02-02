#include "tree_sitter/parser.h"

enum {
  percent_string,
  percent_string_start,
  percent_string_end
};

typedef struct {
  int32_t open_delimiter;
  int32_t close_delimiter;
  uint32_t depth;
} Scanner;

void *tree_sitter_external_tokens_external_scanner_create() {
  Scanner *scanner = malloc(sizeof(Scanner));
  *scanner = (Scanner) {
    .open_delimiter = 0,
    .close_delimiter = 0,
    .depth = 0
  };
  return scanner;
}

void tree_sitter_external_tokens_external_scanner_destroy(void *payload) {
  free(payload);
}

void tree_sitter_external_tokens_external_scanner_reset(void *payload) {}

unsigned tree_sitter_external_tokens_external_scanner_serialize(
  void *payload,
  char *buffer
) { return true; }

void tree_sitter_external_tokens_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

bool tree_sitter_external_tokens_external_scanner_scan(
  void *payload, TSLexer *lexer, const bool *whitelist) {
  Scanner *scanner = payload;

  if (whitelist[percent_string]) {
    while (lexer->lookahead == ' ' ||
           lexer->lookahead == '\t' ||
           lexer->lookahead == '\n' ||
           lexer->lookahead == '\r') {
      lexer->advance(lexer, true);
    }

    if (lexer->lookahead != '%') return false;
    lexer->advance(lexer, false);

    switch (lexer->lookahead) {
      case '(':
        scanner->open_delimiter = '(';
        scanner->close_delimiter = ')';
        scanner->depth = 1;
        break;
      case '[':
        scanner->open_delimiter = '[';
        scanner->close_delimiter = ']';
        scanner->depth = 1;
        break;
      case '{':
        scanner->open_delimiter = '{';
        scanner->close_delimiter = '}';
        scanner->depth = 1;
        break;
      default:
        return false;
    }

    lexer->advance(lexer, false);

    for (;;) {
      if (scanner->depth == 0) {
        lexer->result_symbol = percent_string;
        return true;
      }

      if (lexer->lookahead == scanner->open_delimiter) {
        scanner->depth++;
      } else if (lexer->lookahead == scanner->close_delimiter) {
        scanner->depth--;
      } else if (lexer->lookahead == '#') {
        lexer->advance(lexer, false);
        if (lexer->lookahead == '{') {
          lexer->advance(lexer, false);
          lexer->result_symbol = percent_string_start;
          return true;
        }
      }

      lexer->advance(lexer, false);
    }
  } else if (whitelist[percent_string_end]) {
    if (lexer->lookahead != '}') return false;
    lexer->advance(lexer, false);

    for (;;) {
      if (scanner->depth == 0) {
        lexer->result_symbol = percent_string_end;
        return true;
      }

      if (lexer->lookahead == scanner->open_delimiter) {
        scanner->depth++;
      } else if (lexer->lookahead == scanner->close_delimiter) {
        scanner->depth--;
      }

      lexer->advance(lexer, false);
    }
  }

  return false;
}
