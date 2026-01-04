#include <stdint.h>

__attribute__((noreturn)) void abort(void) { __builtin_trap(); }

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *calloc(size_t nitems, size_t size);
