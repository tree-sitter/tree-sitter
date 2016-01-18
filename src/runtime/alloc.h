#ifndef RUNTIME_ALLOC_H_
#define RUNTIME_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TREE_SITTER_WRAP_MALLOC)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);

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
  return ts_record_free(buffer);
}

#else

#include <stdlib.h>

static inline void *ts_malloc(size_t size) {
  return malloc(size);
}

static inline void *ts_calloc(size_t count, size_t size) {
  return calloc(count, size);
}

static inline void *ts_realloc(void *buffer, size_t size) {
  return realloc(buffer, size);
}

static inline void ts_free(void *buffer) {
  return free(buffer);
}

#endif

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_ALLOC_H_
