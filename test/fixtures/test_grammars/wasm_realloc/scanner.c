#include "tree_sitter/parser.h"

// Constant copied from `crates/language/wasm/src/stdlib.c`,
// Must be kept in sync for a reliable repro. 
#define MAX_HEAP_SIZE (4 * 1024 * 1024)

enum TokenType {
  ZERO_WIDTH_TOKEN
};

void *tree_sitter_wasm_realloc_external_scanner_create(void) {
  size_t large_size = MAX_HEAP_SIZE - 64;
  void *p = malloc(large_size);
  void *q = malloc(4);
  p = realloc(p, 4);
  free(p);
  free(q);
  return NULL;
}

bool tree_sitter_wasm_realloc_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  lexer->result_symbol = ZERO_WIDTH_TOKEN;
  return true;
}

unsigned tree_sitter_wasm_realloc_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  return 0;
}

void tree_sitter_wasm_realloc_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

void tree_sitter_wasm_realloc_external_scanner_destroy(void *payload) {}
