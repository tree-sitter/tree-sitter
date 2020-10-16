#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(TREE_SITTER_TEST)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);
bool ts_toggle_allocation_recording(bool);

static inline void *ts_malloc(size_t size) {
  return ts_record_malloc(size);
}

static inline void *ts_calloc(size_t count, size_t size) {
  return ts_record_calloc(count, size);
}

static inline void *ts_realloc(void *buffer, size_t size) {
  return ts_record_realloc(buffer, size);
}

static inline void ts_free(void *buffer) {
  ts_record_free(buffer);
}

#else

#include <stdlib.h>

static inline bool ts_toggle_allocation_recording(bool value) {
  (void)value;
  return false;
}

#ifndef ts_malloc
#define ts_malloc(_sz)       ts_malloc_dflt(_sz)
#endif
#ifndef ts_calloc
#define ts_calloc(_cnt,_sz)  ts_calloc_dflt(_cnt,_sz)
#endif
#ifndef ts_realloc
#define ts_realloc(_ptr,_sz) ts_realloc_dflt(_ptr,_sz)
#endif
#ifndef ts_free
#define ts_free(_ptr)        ts_free_dflt(_ptr)
#endif

static inline void *ts_malloc_dflt(size_t size) {
  void *result = malloc(size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static inline void *ts_calloc_dflt(size_t count, size_t size) {
  void *result = calloc(count, size);
  if (count > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to allocate %zu bytes", count * size);
    exit(1);
  }
  return result;
}

static inline void *ts_realloc_dflt(void *buffer, size_t size) {
  void *result = realloc(buffer, size);
  if (size > 0 && !result) {
    fprintf(stderr, "tree-sitter failed to reallocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static inline void ts_free_dflt(void *buffer) {
  free(buffer);
}

#endif

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ALLOC_H_
