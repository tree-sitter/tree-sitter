#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC extern void *(*ts_current_malloc)(size_t);
TS_PUBLIC extern void *(*ts_current_calloc)(size_t, size_t);
TS_PUBLIC extern void *(*ts_current_realloc)(void *, size_t);
TS_PUBLIC extern void (*ts_current_free)(void *);

// Allow clients to override allocation functions
#ifdef TREE_SITTER_REUSE_ALLOCATOR

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

#else

#ifndef ts_malloc
#define ts_malloc  malloc
#endif
#ifndef ts_calloc
#define ts_calloc  calloc
#endif
#ifndef ts_realloc
#define ts_realloc realloc
#endif
#ifndef ts_free
#define ts_free    free
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif // TREE_SITTER_ALLOC_H_
