#include "tree_sitter/parser.h"
#include <string.h>

#ifdef __wasm__
  #define panic(x) __builtin_trap()
#else
  #include <assert.h>
  #define panic(x) assert(0)
#endif

enum TokenType {
  ZERO_WIDTH_TOKEN
};

void *tree_sitter_wasm_realloc_clobber_region_external_scanner_create(void) {
  size_t a_count = 32;
  void *a = malloc(a_count);
  memset(a, 0x41, a_count); // fill `a` with 'A's
  for (int i = 0; i < 32; i++) {
    // This condition is unreachable, but it prevents wasi-sdk clang from optimizing
    // out the allocation to `a`.
    if (((char *)a)[i] != 0x41) panic();
  }

  size_t b_count = 16;
  void *b = malloc(b_count);
  memset(b, 0x42, b_count); // fill `b` with 'B's

  // `a` is now first on the free list
  free(a);
  // We're re-allocating the last region, so `realloc`'s optimization to re-use the region
  // by altering its metadata's size (thus avoiding a memcpy) should be used.
  void *c = realloc(b, 24); // realloc `b` should still contain 'B's

  // ensure the contents of `b` were not clobbered. A previous bug caused `a`s region
  // to be used for `c`.
  char *p = (char *)c;
  for (int i = 0; i < (int)b_count; i++) {
    if (p[i] != 0x42) panic();
  }

  free(c);
  return NULL;
}

bool tree_sitter_wasm_realloc_clobber_region_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  lexer->result_symbol = ZERO_WIDTH_TOKEN;
  return true;
}

unsigned tree_sitter_wasm_realloc_clobber_region_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  return 0;
}

void tree_sitter_wasm_realloc_clobber_region_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

void tree_sitter_wasm_realloc_clobber_region_external_scanner_destroy(void *payload) {}
