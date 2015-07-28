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

static inline void tree_vector_push(TreeVector *this, TSTree *tree) {
  if (this->size == this->capacity) {
    this->capacity += 4;
    this->contents = realloc(this->contents, this->capacity * sizeof(TSTree *));
  }
  ts_tree_retain(tree);
  this->contents[this->size++] = tree;
}

static inline void tree_vector_reverse(TreeVector *this) {
  TSTree *swap;
  size_t limit = this->size / 2;
  for (size_t i = 0; i < limit; i++) {
    swap = this->contents[i];
    this->contents[i] = this->contents[this->size - 1 - i];
    this->contents[this->size - 1 - i] = swap;
  }
}

static inline TreeVector tree_vector_copy(TreeVector *this) {
  return (TreeVector){
    .contents = memcpy(malloc(this->capacity * sizeof(TSTree *)),
                       this->contents, this->size * sizeof(TSTree *)),
    .capacity = this->capacity,
    .size = this->size,
  };
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_VECTOR_H_
