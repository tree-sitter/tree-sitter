#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct allocator {
  void *(*malloc)(size_t);
  void *(*calloc)(size_t, size_t);
  void *(*realloc)(void *, size_t);
  void (*free)(void *);
};

extern struct allocator *ts_allocator;

// Allow clients to override allocation functions
#ifndef ts_malloc
#define ts_malloc  ts_allocator->malloc
#endif
#ifndef ts_calloc
#define ts_calloc  ts_allocator->calloc
#endif
#ifndef ts_realloc
#define ts_realloc ts_allocator->realloc
#endif
#ifndef ts_free
#define ts_free    ts_allocator->free
#endif

bool ts_toggle_allocation_recording(bool);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ALLOC_H_
