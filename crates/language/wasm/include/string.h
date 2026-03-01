#ifndef TREE_SITTER_WASM_STRING_H_
#define TREE_SITTER_WASM_STRING_H_

#include <stdint.h>

void *memchr(const void *src, int c, size_t n);

int memcmp(const void *lhs, const void *rhs, size_t count);

void *memcpy(void *restrict dst, const void *restrict src, size_t size);

void *memmove(void *dst, const void *src, size_t count);

void *memset(void *dst, int value, size_t count);

char *strchr(const char *str, int c);

size_t strlen(const char *str);

int strncmp(const char *left, const char *right, size_t n);

#endif // TREE_SITTER_WASM_STRING_H_
