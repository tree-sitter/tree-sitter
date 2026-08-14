#ifndef TREE_SITTER_WASM_STDLIB_H_
#define TREE_SITTER_WASM_STDLIB_H_

#include <stdint.h>

#define NULL ((void*)0)

#if defined(TREE_SITTER_WASM_RUNTIME) && !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name) __attribute__((visibility("default"), export_name(name)))
#elif !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name)
#endif

TS_WASM_EXPORT("malloc") void* malloc(size_t);
TS_WASM_EXPORT("calloc") void* calloc(size_t, size_t);
TS_WASM_EXPORT("free") void free(void*);
TS_WASM_EXPORT("realloc") void* realloc(void*, size_t);

TS_WASM_EXPORT("abort") __attribute__((noreturn)) void abort(void);

#endif // TREE_SITTER_WASM_STDLIB_H_
