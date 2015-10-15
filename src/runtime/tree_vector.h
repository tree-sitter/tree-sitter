#ifndef RUNTIME_TREE_VECTOR_H_
#define RUNTIME_TREE_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "./tree.h"

typedef struct {
  TSTree **contents;
  size_t capacity;
  size_t size;
} TreeVector;

static inline TreeVector tree_vector_new(size_t size) {
  return (TreeVector){
    .contents = malloc(size * sizeof(TSTree *)), .capacity = size, .size = 0,
  };
}

static inline void tree_vector_push(TreeVector *self, TSTree *tree) {
  if (self->size == self->capacity) {
    self->capacity += 4;
    self->contents = realloc(self->contents, self->capacity * sizeof(TSTree *));
  }
  ts_tree_retain(tree);
  self->contents[self->size++] = tree;
}

static inline void tree_vector_reverse(TreeVector *self) {
  TSTree *swap;
  size_t limit = self->size / 2;
  for (size_t i = 0; i < limit; i++) {
    swap = self->contents[i];
    self->contents[i] = self->contents[self->size - 1 - i];
    self->contents[self->size - 1 - i] = swap;
  }
}

static inline TreeVector tree_vector_copy(TreeVector *self) {
  return (TreeVector){
    .contents = memcpy(malloc(self->capacity * sizeof(TSTree *)),
                       self->contents, self->size * sizeof(TSTree *)),
    .capacity = self->capacity,
    .size = self->size,
  };
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_VECTOR_H_
