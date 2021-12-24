#include "alloc.h"

#if defined(TREE_SITTER_ALLOCATION_TRACKING)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);
bool ts_toggle_allocation_recording(bool);

void *(*ts_current_malloc)(size_t) = ts_record_malloc;
void *(*ts_current_calloc)(size_t, size_t) = ts_record_calloc;
void *(*ts_current_realloc)(void *, size_t) = ts_record_realloc;
void (*ts_current_free)(void *) = ts_record_free;

#else

#include <stdlib.h>

bool ts_toggle_allocation_recording(bool value) {
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


// Allow clients to override allocation functions dynamically
void *(*ts_current_malloc)(size_t) = ts_malloc_default;
void *(*ts_current_calloc)(size_t, size_t) = ts_calloc_default;
void *(*ts_current_realloc)(void *, size_t) = ts_realloc_default;
void (*ts_current_free)(void *) = ts_free_default;

#endif // defined(TREE_SITTER_ALLOCATION_TRACKING)

void ts_set_allocator(void *(*new_malloc)(size_t),
                      void *(*new_calloc)(size_t, size_t),
                      void *(*new_realloc)(void *, size_t),
                      void (*new_free)(void *))
{
  ts_current_malloc = new_malloc;
  ts_current_calloc = new_calloc;
  ts_current_realloc = new_realloc;
  ts_current_free = new_free;
}

