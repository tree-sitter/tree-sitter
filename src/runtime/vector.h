#ifndef RUNTIME_VECTOR_H_
#define RUNTIME_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  void *contents;
  size_t size;
  size_t capacity;
  size_t element_size;
} Vector;

static inline Vector vector_new(size_t element_size, size_t capacity) {
  return (Vector){
    .contents = malloc(capacity * element_size),
    .size = 0,
    .capacity = capacity,
    .element_size = element_size,
  };
}

static inline void vector_delete(Vector *self) {
  free(self->contents);
}

static inline void *vector_get(Vector *self, size_t index) {
  assert(index < self->size);
  return (void *)((char *)self->contents + index * self->element_size);
}

static inline void *vector_back(Vector *self)  {
  assert(self->size > 0);
  return vector_get(self, self->size - 1);
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

static inline void vector_push(Vector *self, void *entry) {
  if (self->size == self->capacity) {
    self->capacity += 4;
    self->contents =
      realloc(self->contents, self->capacity * self->element_size);
  }

  char *contents = (char *)self->contents;
  memcpy(contents + (self->size * self->element_size), (char *)entry,
         self->element_size);
  self->size++;
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
  return (Vector){
    .contents = memcpy(malloc(self->capacity * self->element_size),
                       self->contents, self->size * self->element_size),
    .size = self->size,
    .capacity = self->capacity,
    .element_size = self->element_size,
  };
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_VECTOR_H_
