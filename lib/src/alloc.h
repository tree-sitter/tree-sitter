#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#include "tree_sitter/api.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

extern void *(*ts_current_malloc)(size_t);
extern void *(*ts_current_calloc)(size_t, size_t);
extern void *(*ts_current_realloc)(void *, size_t);
extern void (*ts_current_free)(void *);

// Allow clients to override allocation functions
#ifndef ts_malloc
#define ts_malloc  ts_current_malloc
#endif
#ifndef ts_calloc
#define ts_calloc  ts_current_calloc
#endif
#ifndef ts_realloc
#define ts_realloc ts_current_realloc
#endif
#ifndef ts_free
#define ts_free    ts_current_free
#endif

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ALLOC_H_
