#ifndef TREE_SITTER_WASM_STDLIB_H_
#define TREE_SITTER_WASM_STDLIB_H_

#include <stdint.h>

#define NULL ((void*)0)

void* malloc(size_t);
void* calloc(size_t, size_t);
void free(void*);
void* realloc(void*, size_t);

__attribute__((noreturn)) void abort(void);

#endif // TREE_SITTER_WASM_STDLIB_H_
