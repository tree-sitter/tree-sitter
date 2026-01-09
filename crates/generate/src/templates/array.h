#ifndef TREE_SITTER_ARRAY_H_
#define TREE_SITTER_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "./alloc.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4101)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

typedef struct {
  uint32_t size;
  uint32_t capacity;
} _ArrayMeta;

#define Array(T)    \
  struct {          \
    T *contents;    \
    _ArrayMeta meta; \
  }

/// Initialize an array.
#define array_init(self) \
  ((self)->meta.size = 0, (self)->meta.capacity = 0, (self)->contents = NULL)

/// Create an empty array.
#define array_new() \
  { NULL, { 0, 0 } }

/// Get a pointer to the element at a given `index` in the array.
#define array_get(self, _index) \
  (assert((uint32_t)(_index) < (self)->meta.size), &(self)->contents[_index])

/// Get a pointer to the first element in the array.
#define array_front(self) array_get(self, 0)

/// Get a pointer to the last element in the array.
#define array_back(self) array_get(self, (self)->meta.size - 1)

/// Clear the array, setting its size to zero. Note that this does not free any
/// memory allocated for the array's contents.
#define array_clear(self) ((self)->meta.size = 0)

/// Reserve `new_capacity` elements of space in the array. If `new_capacity` is
/// less than the array's current capacity, this function has no effect.
#define array_reserve(self, new_capacity) \
 (self)->contents = _array__reserve(&(self)->meta, (self)->contents, array_elem_size(self), new_capacity)

/// Free any memory allocated for this array. Note that this does not free any
/// memory allocated for the array's contents.
#define array_delete(self) _array__delete((self)->contents, (self), sizeof(*self))

/// Push a new `element` onto the end of the array.
#define array_push(self, element)                            \
  ((self)->contents = _array__grow(&(self)->meta, (self)->contents, 1, \
                                  array_elem_size(self)), \
   (self)->contents[(self)->meta.size++] = (element))

/// Increase the array's size by `count` elements.
/// New elements are zero-initialized.
#define array_grow_by(self, count) \
  do { \
    if ((count) == 0) break; \
    (self)->contents = _array__grow(&(self)->meta, (self)->contents, count, array_elem_size(self)); \
    memset((self)->contents + (self)->meta.size, 0, (count) * array_elem_size(self)); \
    (self)->meta.size += (count); \
  } while (0)

/// Append all elements from one array to the end of another.
#define array_push_all(self, other) \
  array_extend((self), (other)->meta.size, (other)->contents)

/// Append `count` elements to the end of the array, reading their values from the
/// `contents` pointer.
#define array_extend(self, count, new_contents)                                \
  (self)->contents = _array__splice(                                           \
                       &(self)->meta, (self)->contents, array_elem_size(self), \
                       (self)->meta.size, 0, (count), (new_contents))

/// Remove `old_count` elements from the array starting at the given `index`. At
/// the same index, insert `new_count` new elements, reading their values from the
/// `new_contents` pointer.
#define array_splice(self, _index, old_count, new_count, new_contents)         \
  (self)->contents = _array__splice(                                           \
                       &(self)->meta, (self)->contents, array_elem_size(self), \
                       (_index), (old_count), (new_count), (new_contents))

/// Insert one `element` into the array at the given `index`.
#define array_insert(self, _index, element)                          \
  (self)->contents = _array__splice(&(self)->meta, (self)->contents, \
                       array_elem_size(self), _index, 0, 1, &(element))

/// Remove one element from the array at the given `index`.
#define array_erase(self, _index) \
  _array__erase(&(self)->meta, (self)->contents, array_elem_size(self), _index)

/// Pop the last element off the array, returning the element by value.
#define array_pop(self) ((self)->contents[--(self)->meta.size])

/// Assign the contents of one array to another, reallocating if necessary.
#define array_assign(self, other) \
  (self)->contents = _array__assign(&(self)->meta, (self)->contents, &(other)->meta, (other)->contents, array_elem_size(self))

/// Swap one array with another
#define array_swap(self, other) \
  do { \
    _ArrayMeta swapMeta = (other)->meta; \
    void* swapContents = (other)->contents; \
    *(other) = *(self); \
    (self)->meta = swapMeta; \
    (self)->contents = swapContents; \
  } while(0)

/// Get the size of the array contents
#define array_elem_size(self) (sizeof *(self)->contents)

/// Search a sorted array for a given `needle` value, using the given `compare`
/// callback to determine the order.
///
/// If an existing element is found to be equal to `needle`, then the `index`
/// out-parameter is set to the existing value's index, and the `exists`
/// out-parameter is set to true. Otherwise, `index` is set to an index where
/// `needle` should be inserted in order to preserve the sorting, and `exists`
/// is set to false.
#define array_search_sorted_with(self, compare, needle, _index, _exists) \
  _array__search_sorted(self, 0, compare, , needle, _index, _exists)

/// Search a sorted array for a given `needle` value, using integer comparisons
/// of a given struct field (specified with a leading dot) to determine the order.
///
/// See also `array_search_sorted_with`.
#define array_search_sorted_by(self, field, needle, _index, _exists) \
  _array__search_sorted(self, 0, _compare_int, field, needle, _index, _exists)

/// Insert a given `value` into a sorted array, using the given `compare`
/// callback to determine the order.
#define array_insert_sorted_with(self, compare, value) \
  do { \
    unsigned _index, _exists; \
    array_search_sorted_with(self, compare, &(value), &_index, &_exists); \
    if (!_exists) array_insert(self, _index, value); \
  } while (0)

/// Insert a given `value` into a sorted array, using integer comparisons of
/// a given struct field (specified with a leading dot) to determine the order.
///
/// See also `array_search_sorted_by`.
#define array_insert_sorted_by(self, field, value) \
  do { \
    unsigned _index, _exists; \
    array_search_sorted_by(self, field, (value) field, &_index, &_exists); \
    if (!_exists) array_insert(self, _index, value); \
  } while (0)

// Private

/// This is not what you're looking for, see `array_delete`.
static inline void _array__delete(void *self_contents, void *vself, size_t vselfsize) {
  if (self_contents) {
    ts_free(self_contents);
    memset(vself, 0, vselfsize);
  }
}

/// This is not what you're looking for, see `array_erase`.
static inline void _array__erase(_ArrayMeta *self_meta, void *self_contents, size_t element_size,
                                uint32_t index) {
  assert(index < self_meta->size);
  char *contents = self_contents;
  memmove(contents + index * element_size, contents + (index + 1) * element_size,
          (self_meta->size - index - 1) * element_size);
  self_meta->size--;
}

/// This is not what you're looking for, see `array_reserve`.
static inline void *_array__reserve(_ArrayMeta *self_meta, void *self_contents, size_t element_size, uint32_t new_capacity) {
  if (new_capacity > self_meta->capacity) {
    self_meta->capacity = new_capacity;
    if (self_contents) {
      return ts_realloc(self_contents, new_capacity * element_size);
    } else {
      return ts_malloc(new_capacity * element_size);
    }
  }
  return self_contents;
}

/// This is not what you're looking for, see `array_assign`.
static inline void* _array__assign(_ArrayMeta *self_meta, void *self_contents, const _ArrayMeta *other_meta, const void *other_contents, size_t element_size) {
  void *new_self_contents = _array__reserve(self_meta, self_contents, element_size, other_meta->size);
  self_meta->size = other_meta->size;
  memcpy(new_self_contents, other_contents, self_meta->size * element_size);
  return new_self_contents;
}

/// This is not what you're looking for, see `array_push` or `array_grow_by`.
static inline void *_array__grow(_ArrayMeta *self_meta, void *self_contents, uint32_t count, size_t element_size) {
  uint32_t new_size = self_meta->size + count;
  if (new_size > self_meta->capacity) {
    uint32_t new_capacity = self_meta->capacity * 2;
    if (new_capacity < 8) new_capacity = 8;
    if (new_capacity < new_size) new_capacity = new_size;
    return _array__reserve(self_meta, self_contents, element_size, new_capacity);
  }
  return self_contents;
}

/// This is not what you're looking for, see `array_splice`.
static inline void* _array__splice(_ArrayMeta *self_meta, void *self_contents, size_t element_size,
                                 uint32_t index, uint32_t old_count,
                                 uint32_t new_count, const void *elements) {
  uint32_t new_size = self_meta->size + new_count - old_count;
  uint32_t old_end = index + old_count;
  uint32_t new_end = index + new_count;
  assert(old_end <= self_meta->size);

  char *contents = _array__reserve(self_meta, self_contents, element_size, new_size);

  if (self_meta->size > old_end) {
    memmove(
      contents + new_end * element_size,
      contents + old_end * element_size,
      (self_meta->size - old_end) * element_size
    );
  }
  if (new_count > 0) {
    if (elements) {
      memcpy(
        (contents + index * element_size),
        elements,
        new_count * element_size
      );
    } else {
      memset(
        (contents + index * element_size),
        0,
        new_count * element_size
      );
    }
  }
  self_meta->size += new_count - old_count;

  return contents;
}

/// A binary search routine, based on Rust's `std::slice::binary_search_by`.
/// This is not what you're looking for, see `array_search_sorted_with` or `array_search_sorted_by`.
#define _array__search_sorted(self, start, compare, suffix, needle, _index, _exists) \
  do { \
    *(_index) = start; \
    *(_exists) = false; \
    uint32_t size = (self)->meta.size - *(_index); \
    if (size == 0) break; \
    int comparison; \
    while (size > 1) { \
      uint32_t half_size = size / 2; \
      uint32_t mid_index = *(_index) + half_size; \
      comparison = compare(&((self)->contents[mid_index] suffix), (needle)); \
      if (comparison <= 0) *(_index) = mid_index; \
      size -= half_size; \
    } \
    comparison = compare(&((self)->contents[*(_index)] suffix), (needle)); \
    if (comparison == 0) *(_exists) = true; \
    else if (comparison < 0) *(_index) += 1; \
  } while (0)

/// Helper macro for the `_sorted_by` routines below. This takes the left (existing)
/// parameter by reference in order to work with the generic sorting function above.
#define _compare_int(a, b) ((int)*(a) - (int)(b))

#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ARRAY_H_
