#ifndef RUNTIME_ALLOC_H_
#define RUNTIME_ALLOC_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_ALLOC_H_
