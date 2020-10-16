#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Allow clients to override allocation functions

#ifndef ts_malloc
#define ts_malloc(size)         ts_malloc_default(size)
#endif
#ifndef ts_calloc
#define ts_calloc(count,size)   ts_calloc_default(count,size)
#endif
#ifndef ts_realloc
#define ts_realloc(buffer,size) ts_realloc_default(buffer,size)
#endif
#ifndef ts_free
#define ts_free(buffer)         ts_free_default(buffer)
#endif

#if defined(TREE_SITTER_TEST)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);
bool ts_toggle_allocation_recording(bool);

static inline void *ts_malloc_default(size_t size) {
  return ts_record_malloc(size);
}

static inline void *ts_calloc_default(size_t count, size_t size) {
  return ts_record_calloc(count, size);
}

static inline void *ts_realloc_default(void *buffer, size_t size) {
  return ts_record_realloc(buffer, size);
}

static inline void ts_free_default(void *buffer) {
  ts_record_free(buffer);
}

#else

#include <stdlib.h>

static inline bool ts_toggle_allocation_recording(bool value) {
  (void)value;
  return false;
}


static inline void *ts_malloc_default(size_t size) {
  void *result = malloc(size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static inline void *ts_calloc_default(size_t count, size_t size) {
  void *result = calloc(count, size);
  if (count > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", count * size);
    exit(1);
  }
  return result;
}

static inline void *ts_realloc_default(void *buffer, size_t size) {
  void *result = realloc(buffer, size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to reallocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static inline void ts_free_default(void *buffer) {
  free(buffer);
}

#endif

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ALLOC_H_
