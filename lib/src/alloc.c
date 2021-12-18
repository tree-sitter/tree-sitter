#include "alloc.h"

#if defined(TREE_SITTER_ALLOCATION_TRACKING)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);
bool ts_toggle_allocation_recording(bool);

static TSAllocator ts_tracking_allocator = {
  .malloc = ts_record_malloc,
  .calloc = ts_record_calloc,
  .realloc = ts_record_realloc,
  .free = ts_record_free,
};

TSAllocator *ts_allocator = &ts_tracking_allocator;

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

static TSAllocator ts_default_allocator = {
  .malloc = ts_malloc_default,
  .calloc = ts_calloc_default,
  .realloc = ts_realloc_default,
  .free = ts_free_default,
};

// Allow clients to override allocation functions dynamically
TSAllocator *ts_allocator = &ts_default_allocator;

#endif // defined(TREE_SITTER_ALLOCATION_TRACKING)

bool ts_set_allocator(TSAllocator *new_alloc)
{
  static bool using_default_allocator = true;
  if (!using_default_allocator) {
    fprintf(stderr, "tree-sitter's allocator can only be set once!");
    return false;
  }
  using_default_allocator = false;
  ts_allocator = new_alloc;
  return true;
}

