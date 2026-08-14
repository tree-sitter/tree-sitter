#ifndef TREE_SITTER_WASM_STRING_H_
#define TREE_SITTER_WASM_STRING_H_

#include <stdint.h>

#if defined(TREE_SITTER_WASM_RUNTIME) && !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name) __attribute__((visibility("default"), export_name(name)))
#elif !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name)
#endif

TS_WASM_EXPORT("memchr") void *memchr(const void *src, int c, size_t n);

TS_WASM_EXPORT("memcmp") int memcmp(const void *lhs, const void *rhs, size_t count);

TS_WASM_EXPORT("memcpy") void *memcpy(void *restrict dst, const void *restrict src, size_t size);

TS_WASM_EXPORT("memmove") void *memmove(void *dst, const void *src, size_t count);

TS_WASM_EXPORT("memset") void *memset(void *dst, int value, size_t count);

TS_WASM_EXPORT("strchr") char *strchr(const char *str, int c);

TS_WASM_EXPORT("strcmp") int strcmp(const char *left, const char *right);

TS_WASM_EXPORT("strlen") size_t strlen(const char *str);

TS_WASM_EXPORT("strncat") char *strncat(char *restrict dest, const char *restrict src, size_t count);

TS_WASM_EXPORT("strncmp") int strncmp(const char *left, const char *right, size_t n);

TS_WASM_EXPORT("strncpy") char *strncpy(char *restrict dest, const char *restrict src, size_t count);

#endif // TREE_SITTER_WASM_STRING_H_
