#include "alloc.h"
#include <stdlib.h>

static void *ts_malloc_default(size_t size) {
  void *result = malloc(size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static void *ts_calloc_default(size_t count, size_t size) {
  void *result = calloc(count, size);
  if (count > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", count * size);
    exit(1);
  }
  return result;
}

static void *ts_realloc_default(void *buffer, size_t size) {
  void *result = realloc(buffer, size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to reallocate %zu bytes", size);
    exit(1);
  }
  return result;
}

// Allow clients to override allocation functions dynamically
void *(*ts_current_malloc)(size_t) = ts_malloc_default;
void *(*ts_current_calloc)(size_t, size_t) = ts_calloc_default;
void *(*ts_current_realloc)(void *, size_t) = ts_realloc_default;
void (*ts_current_free)(void *) = free;

void ts_set_allocator(
  void *(*new_malloc)(size_t),
  void *(*new_calloc)(size_t, size_t),
  void *(*new_realloc)(void *, size_t),
  void (*new_free)(void *)
) {
  ts_current_malloc = new_malloc ? new_malloc : ts_malloc_default;
  ts_current_calloc = new_calloc ? new_calloc : ts_calloc_default;
  ts_current_realloc = new_realloc ? new_realloc : ts_realloc_default;
  ts_current_free = new_free ? new_free : free;
}

