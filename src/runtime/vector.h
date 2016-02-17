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

#define Vector(T)    \
  struct {           \
    T *contents;     \
    size_t size;     \
    size_t capacity; \
  }

#define vector_init(self) \
  ((self)->size = 0, (self)->capacity = 0, (self)->contents = NULL)

#define vector_get(self, index) \
  (assert((size_t)index < (self)->size), &(self)->contents[index])

#define vector_front(self) vector_get(self, 0)

#define vector_back(self) vector_get(self, (self)->size - 1)

#define vector_clear(self) ((self)->size = 0)

#define vector_grow(self, new_capacity) \
  vector__grow((VoidVector *)(self), vector__elem_size(self), new_capacity)

#define vector_erase(self, index) \
  vector__erase((VoidVector *)(self), vector__elem_size(self), index)

#define vector_delete(self) vector__delete((VoidVector *)self)

#define vector_push(self, element)                \
  (((self)->size < (self)->capacity ||            \
    vector_grow((self), (self)->capacity * 2)) && \
   ((self)->contents[(self)->size++] = (element), true))

#define vector_pop(self) ((self)->contents[--(self)->size])

#define vector_reverse(self) \
  vector__reverse((VoidVector *)(self), vector__elem_size(self))

#define vector_copy(self)                                            \
  {                                                                  \
    memcpy(ts_calloc((self)->capacity, vector__elem_size(self)),     \
           (self)->contents, (self)->size *vector__elem_size(self)), \
      (self)->size, (self)->capacity,                                \
  }

// Private

typedef Vector(void) VoidVector;

#define vector__elem_size(self) sizeof(*(self)->contents)

static inline void vector__delete(VoidVector *self) {
  ts_free(self->contents);
  self->contents = NULL;
  self->size = 0;
  self->capacity = 0;
}

static inline void vector__erase(VoidVector *self, size_t element_size,
                                 size_t index) {
  assert(index < self->size);
  char *contents = (char *)self->contents;
  memmove(contents + index * element_size, contents + (index + 1) * element_size,
          (self->size - index - 1) * element_size);
  self->size--;
}

static inline bool vector__grow(VoidVector *self, size_t element_size,
                                size_t new_capacity) {
  if (new_capacity == 0)
    return true;

  void *new_contents;
  if (self->contents)
    new_contents = ts_realloc(self->contents, new_capacity * element_size);
  else
    new_contents = ts_calloc(new_capacity, element_size);

  if (!new_contents)
    return false;
  self->capacity = new_capacity;
  self->contents = new_contents;
  return true;
}

static inline void vector__reverse(VoidVector *self, size_t element_size) {
  char swap[element_size];
  char *contents = (char *)self->contents;
  for (size_t i = 0, limit = self->size / 2; i < limit; i++) {
    size_t offset = i * element_size;
    size_t reverse_offset = (self->size - 1 - i) * element_size;
    memcpy(&swap, contents + offset, element_size);
    memcpy(contents + offset, contents + reverse_offset, element_size);
    memcpy(contents + reverse_offset, &swap, element_size);
  }
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_VECTOR_H_
