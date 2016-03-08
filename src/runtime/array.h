#ifndef RUNTIME_ARRAY_H_
#define RUNTIME_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "runtime/alloc.h"

#define Array(T)     \
  struct {           \
    T *contents;     \
    size_t size;     \
    size_t capacity; \
  }

#define array_init(self) \
  ((self)->size = 0, (self)->capacity = 0, (self)->contents = NULL)

#define array_new() \
  { NULL, 0, 0 }

#define array_get(self, index) \
  (assert((size_t)index < (self)->size), &(self)->contents[index])

#define array_front(self) array_get(self, 0)

#define array_back(self) array_get(self, (self)->size - 1)

#define array_clear(self) ((self)->size = 0)

#define array_grow(self, new_capacity) \
  array__grow((VoidArray *)(self), array__elem_size(self), new_capacity)

#define array_erase(self, index) \
  array__erase((VoidArray *)(self), array__elem_size(self), index)

#define array_delete(self) array__delete((VoidArray *)self)

#define array_push(self, element)                                       \
  (((self)->size < (self)->capacity ||                                  \
    array_grow((self), (self)->capacity ? (self)->capacity * 2 : 4)) && \
   ((self)->contents[(self)->size++] = (element), true))

#define array_splice(self, index, old_count, new_count, new_elements)          \
  array__splice((VoidArray *)(self), array__elem_size(self), index, old_count, \
                new_count, new_elements)

#define array_pop(self) ((self)->contents[--(self)->size])

#define array_reverse(self) \
  array__reverse((VoidArray *)(self), array__elem_size(self))

#define array_copy(self)                                            \
  {                                                                 \
    memcpy(ts_calloc((self)->capacity, array__elem_size(self)),     \
           (self)->contents, (self)->size *array__elem_size(self)), \
      (self)->size, (self)->capacity,                               \
  }

// Private

typedef Array(void) VoidArray;

#define array__elem_size(self) sizeof(*(self)->contents)

static inline void array__delete(VoidArray *self) {
  ts_free(self->contents);
  self->contents = NULL;
  self->size = 0;
  self->capacity = 0;
}

static inline void array__erase(VoidArray *self, size_t element_size,
                                size_t index) {
  assert(index < self->size);
  char *contents = (char *)self->contents;
  memmove(contents + index * element_size, contents + (index + 1) * element_size,
          (self->size - index - 1) * element_size);
  self->size--;
}

static inline bool array__grow(VoidArray *self, size_t element_size,
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

static inline bool array__splice(VoidArray *self, size_t element_size,
                                 size_t index, size_t old_count,
                                 size_t new_count, void *elements) {
  assert(index + old_count <= self->size);
  assert(index < self->size);
  size_t new_size = self->size + new_count - old_count;
  size_t old_end = index + old_count;
  size_t new_end = index + new_count;
  if (new_size >= self->capacity) {
    if (!array__grow(self, element_size, new_size))
      return false;
  }

  char *contents = (char *)self->contents;
  if (self->size > old_end)
    memmove(contents + new_end * element_size, contents + old_end * element_size,
            (self->size - old_end) * element_size);
  if (new_count > 0)
    memcpy((contents + index * element_size), elements,
           new_count * element_size);
  self->size += new_count - old_count;
  return true;
}

static inline void array__reverse(VoidArray *self, size_t element_size) {
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

#endif  // RUNTIME_ARRAY_H_
