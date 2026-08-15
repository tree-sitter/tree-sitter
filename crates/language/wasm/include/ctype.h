#ifndef TREE_SITTER_WASM_CTYPE_H_
#define TREE_SITTER_WASM_CTYPE_H_

typedef void *locale_t;

#ifndef weak_alias
#define weak_alias(old, new) \
  extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))
#endif

int isblank(int c);

static inline int isprint(int c) {
  return c >= 0x20 && c <= 0x7E;
}

#endif // TREE_SITTER_WASM_CTYPE_H_
