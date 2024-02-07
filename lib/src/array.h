#ifndef TREE_SITTER_ARRAY_H_
#define TREE_SITTER_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "./alloc.h"

#define Array(T) \
  struct { \
    T *contents; \
    uint32_t size; \
    uint32_t capacity; \
  }

#define array_init(self) ((self)->size = 0, (self)->capacity = 0, (self)->contents = NULL)

#define array_new() \
  { NULL, 0, 0 }

#define array_get(self, _index) \
  (assert((uint32_t)(_index) < (self)->size), &(self)->contents[_index])

#define array_front(self) array_get(self, 0)

#define array_back(self)  array_get(self, (self)->size - 1)

#define array_clear(self) ((self)->size = 0)

#define array_reserve(self, new_capacity) \
  array__reserve((VoidArray *)(self), array__elem_size(self), new_capacity)

// Free any memory allocated for this array.
#define array_delete(self) array__delete((VoidArray *)(self))

#define array_push(self, element) \
  (array__grow((VoidArray *)(self), 1, array__elem_size(self)), \
   (self)->contents[(self)->size++] = (element))

// Increase the array's size by a given number of elements, reallocating
// if necessary. New elements are zero-initialized.
#define array_grow_by(self, count) \
  (array__grow((VoidArray *)(self), count, array__elem_size(self)), \
   memset((self)->contents + (self)->size, 0, (count) * array__elem_size(self)), \
   (self)->size += (count))

#define array_push_all(self, other) array_extend((self), (other)->size, (other)->contents)

// Append `count` elements to the end of the array, reading their values from the
// `contents` pointer.
#define array_extend(self, count, contents) \
  array__splice((VoidArray *)(self), array__elem_size(self), (self)->size, 0, count, contents)

// Remove `old_count` elements from the array starting at the given `index`. At
// the same index, insert `new_count` new elements, reading their values from the
// `new_contents` pointer.
#define array_splice(self, _index, old_count, new_count, new_contents) \
  array__splice( \
    (VoidArray *)(self), array__elem_size(self), _index, old_count, new_count, new_contents \
  )

// Insert one `element` into the array at the given `index`.
#define array_insert(self, _index, element) \
  array__splice((VoidArray *)(self), array__elem_size(self), _index, 0, 1, &(element))

// Remove one `element` from the array at the given `index`.
#define array_erase(self, _index) array__erase((VoidArray *)(self), array__elem_size(self), _index)

#define array_pop(self)           ((self)->contents[--(self)->size])

#define array_assign(self, other) \
  array__assign((VoidArray *)(self), (const VoidArray *)(other), array__elem_size(self))

#define array_swap(self, other) array__swap((VoidArray *)(self), (VoidArray *)(other))

// Search a sorted array for a given `needle` value, using the given `compare`
// callback to determine the order.
//
// If an existing element is found to be equal to `needle`, then the `index`
// out-parameter is set to the existing value's index, and the `exists`
// out-parameter is set to true. Otherwise, `index` is set to an index where
// `needle` should be inserted in order to preserve the sorting, and `exists`
// is set to false.
#define array_search_sorted_with(self, compare, needle, _index, _exists) \
  array__search_sorted(self, 0, compare, , needle, _index, _exists)

// Search a sorted array for a given `needle` value, using integer comparisons
// of a given struct field (specified with a leading dot) to determine the order.
//
// See also `array_search_sorted_with`.
#define array_search_sorted_by(self, field, needle, _index, _exists) \
  array__search_sorted(self, 0, compare_int, field, needle, _index, _exists)

// Insert a given `value` into a sorted array, using the given `compare`
// callback to determine the order.
#define array_insert_sorted_with(self, compare, value) \
  do { \
    unsigned _index, _exists; \
    array_search_sorted_with(self, compare, &(value), &_index, &_exists); \
    if (!_exists) \
      array_insert(self, _index, value); \
  } while (0)

// Insert a given `value` into a sorted array, using integer comparisons of
// a given struct field (specified with a leading dot) to determine the order.
//
// See also `array_search_sorted_by`.
#define array_insert_sorted_by(self, field, value) \
  do { \
    unsigned _index, _exists; \
    array_search_sorted_by(self, field, (value)field, &_index, &_exists); \
    if (!_exists) \
      array_insert(self, _index, value); \
  } while (0)

// Private

typedef Array(void) VoidArray;

#define array__elem_size(self) sizeof(*(self)->contents)

static inline void array__delete(VoidArray *self) {
  if (self->contents) {
    ts_free(self->contents);
    self->contents = NULL;
    self->size = 0;
    self->capacity = 0;
  }
}

static inline void array__erase(VoidArray *self, size_t element_size, uint32_t index) {
  assert(index < self->size);
  char *contents = (char *)self->contents;
  memmove(
    contents + index * element_size, contents + (index + 1) * element_size,
    (self->size - index - 1) * element_size
  );
  self->size--;
}

static inline void array__reserve(VoidArray *self, size_t element_size, uint32_t new_capacity) {
  if (new_capacity > self->capacity) {
    if (self->contents) {
      self->contents = ts_realloc(self->contents, new_capacity * element_size);
    } else {
      self->contents = ts_malloc(new_capacity * element_size);
    }
    self->capacity = new_capacity;
  }
}

static inline void array__assign(VoidArray *self, const VoidArray *other, size_t element_size) {
  array__reserve(self, element_size, other->size);
  self->size = other->size;
  memcpy(self->contents, other->contents, self->size * element_size);
}

static inline void array__swap(VoidArray *self, VoidArray *other) {
  VoidArray swap = *other;
  *other = *self;
  *self = swap;
}

static inline void array__grow(VoidArray *self, uint32_t count, size_t element_size) {
  uint32_t new_size = self->size + count;
  if (new_size > self->capacity) {
    uint32_t new_capacity = self->capacity * 2;
    if (new_capacity < 8)
      new_capacity = 8;
    if (new_capacity < new_size)
      new_capacity = new_size;
    array__reserve(self, element_size, new_capacity);
  }
}

static inline void array__splice(
  VoidArray *self, size_t element_size, uint32_t index, uint32_t old_count, uint32_t new_count,
  const void *elements
) {
  uint32_t new_size = self->size + new_count - old_count;
  uint32_t old_end = index + old_count;
  uint32_t new_end = index + new_count;
  assert(old_end <= self->size);

  array__reserve(self, element_size, new_size);

  char *contents = (char *)self->contents;
  if (self->size > old_end) {
    memmove(
      contents + new_end * element_size, contents + old_end * element_size,
      (self->size - old_end) * element_size
    );
  }
  if (new_count > 0) {
    if (elements) {
      memcpy((contents + index * element_size), elements, new_count * element_size);
    } else {
      memset((contents + index * element_size), 0, new_count * element_size);
    }
  }
  self->size += new_count - old_count;
}

// A binary search routine, based on Rust's `std::slice::binary_search_by`.
#define array__search_sorted(self, start, compare, suffix, needle, _index, _exists) \
  do { \
    *(_index) = start; \
    *(_exists) = false; \
    uint32_t size = (self)->size - *(_index); \
    if (size == 0) \
      break; \
    int comparison; \
    while (size > 1) { \
      uint32_t half_size = size / 2; \
      uint32_t mid_index = *(_index) + half_size; \
      comparison = compare(&((self)->contents[mid_index] suffix), (needle)); \
      if (comparison <= 0) \
        *(_index) = mid_index; \
      size -= half_size; \
    } \
    comparison = compare(&((self)->contents[*(_index)] suffix), (needle)); \
    if (comparison == 0) \
      *(_exists) = true; \
    else if (comparison < 0) \
      *(_index) += 1; \
  } while (0)

// Helper macro for the `_sorted_by` routines below. This takes the left (existing)
// parameter by reference in order to work with the generic sorting function above.
#define compare_int(a, b) ((int)*(a) - (int)(b))

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ARRAY_H_
