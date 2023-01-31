#include <string.h>
#include <tree_sitter/parser.h>

enum {
  EXTERNAL,
};

void *tree_sitter_external_force_serialize_external_scanner_create() {
  int* counter = (int*) malloc(sizeof(int));
  *counter = 0;
  return counter;
}

void tree_sitter_external_force_serialize_external_scanner_destroy(
  void *payload) {
  free(payload);
}

unsigned tree_sitter_external_force_serialize_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  memcpy(buffer, payload, sizeof(int));
  return sizeof(int); 
}

void tree_sitter_external_force_serialize_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
  int* counter = (int*) payload;
  *counter = 0;
  if (length >= sizeof(int)) {
    memcpy(payload, buffer, sizeof(int));
  }
}

bool tree_sitter_external_force_serialize_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  while (lexer->lookahead == ' ') {
    lexer->advance(lexer, true);
  }

  if (lexer->lookahead != ' ') {
    int* counter = (int*) payload;
    (*counter)++;
    if (*counter == 3) {
      while (lexer->lookahead >= 'a' && lexer->lookahead <= 'z') {
        lexer->advance(lexer, false);
      }
      lexer->result_symbol = EXTERNAL;
      return true;
    }
  }

  // Force serialization of the state, even when returning false.
  // Without this, the counter will not increment to 3 and the external symbol
  // will never be scanned.
  lexer->force_serialize_state = true;

  return false;
}
