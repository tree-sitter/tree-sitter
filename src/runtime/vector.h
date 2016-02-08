#ifndef RUNTIME_VECTOR_H_
#define RUNTIME_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "runtime/alloc.h"

typedef struct {
  void *contents;
  size_t size;
  size_t capacity;
  size_t element_size;
} Vector;

static inline Vector vector_new(size_t element_size) {
  Vector result;
  result.contents = NULL;
  result.size = 0;
  result.capacity = 0;
  result.element_size = element_size;
  return result;
}

static inline bool vector_grow(Vector *self, size_t capacity) {
  if (capacity == 0)
    return true;

  void *new_contents;
  if (self->contents)
    new_contents = ts_realloc(self->contents, capacity * self->element_size);
  else
    new_contents = ts_calloc(capacity, self->element_size);

  if (!new_contents)
    return false;
  self->capacity = capacity;
  self->contents = new_contents;
  return true;
}

static inline bool vector_valid(Vector *self) {
  return self->element_size > 0;
}

static inline void vector_delete(Vector *self) {
  if (self->contents) {
    ts_free(self->contents);
    self->contents = NULL;
    self->size = 0;
    self->capacity = 0;
  }
}

static inline void *vector_get(Vector *self, size_t index) {
  assert(index < self->size);
  return (void *)((char *)self->contents + index * self->element_size);
}

static inline void vector_set(Vector *self, size_t index, void *entry) {
  assert(index < self->size);
  char *location = (char *)self->contents + index * self->element_size;
  memcpy(location, (char *)entry, self->element_size);
}

static inline void *vector_back(Vector *self) {
  assert(self->size > 0);
  return vector_get(self, self->size - 1);
}

static inline void *vector_pop(Vector *self) {
  void *result = vector_back(self);
  self->size--;
  return result;
}

static inline void vector_clear(Vector *self) {
  self->size = 0;
}

static inline void vector_erase(Vector *self, size_t index) {
  assert(index < self->size);
  char *contents = (char *)self->contents;
  memmove(contents + index * self->element_size,
          contents + (index + 1) * self->element_size,
          (self->size - index - 1) * self->element_size);
  self->size--;
}

static inline bool vector_push(Vector *self, void *entry) {
  if (self->size == self->capacity) {
    self->capacity += 4;
    void *contents =
      ts_realloc(self->contents, self->capacity * self->element_size);
    if (!contents)
      return false;
    self->contents = contents;
  }

  self->size++;
  vector_set(self, self->size - 1, entry);
  return true;
}

static inline void vector_reverse(Vector *self) {
  char swap[self->element_size];
  char *contents = (char *)self->contents;
  size_t limit = self->size / 2;
  for (size_t i = 0; i < limit; i++) {
    size_t offset = i * self->element_size;
    size_t reverse_offset = (self->size - 1 - i) * self->element_size;
    memcpy(&swap, contents + offset, self->element_size);
    memcpy(contents + offset, contents + reverse_offset, self->element_size);
    memcpy(contents + reverse_offset, &swap, self->element_size);
  }
}

static inline Vector vector_copy(Vector *self) {
  Vector copy = *self;
  copy.contents = memcpy(ts_calloc(self->capacity, self->element_size),
                         self->contents, self->size * self->element_size);
  return copy;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_VECTOR_H_
