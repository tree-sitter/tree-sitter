#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include <stdlib.h>
#include <stdbool.h>
#include "runtime/point.h"
#include "tree_sitter/runtime.h"

typedef struct {
  size_t bytes;
  size_t chars;
  TSPoint extent;
} Length;

static inline bool length_has_unknown_chars(Length self) {
  return self.bytes > 0 && self.chars == 0;
}

static inline void length_set_unknown_chars(Length *self) {
  self->chars = 0;
}

static inline Length length_min(Length len1, Length len2) {
  return (len1.chars < len2.chars) ? len1 : len2;
}

static inline Length length_add(Length len1, Length len2) {
  Length result;
  result.chars = len1.chars + len2.chars;
  result.bytes = len1.bytes + len2.bytes;
  result.extent = point_add(len1.extent, len2.extent);

  if (length_has_unknown_chars(len1) || length_has_unknown_chars(len2)) {
    result.chars = 0;
  } else {
    result.chars = len1.chars + len2.chars;
  }

  return result;
}

static inline Length length_sub(Length len1, Length len2) {
  Length result;
  result.bytes = len1.bytes - len2.bytes;
  result.extent = point_sub(len1.extent, len2.extent);

  if (length_has_unknown_chars(len1) || length_has_unknown_chars(len2)) {
    result.chars = 0;
  } else {
    result.chars = len1.chars - len2.chars;
  }

  return result;
}

static inline Length length_zero() {
  return (Length){ 0, 0, {0, 0} };
}

static inline bool length_eq(Length self, Length other) {
  return self.bytes == other.bytes && self.chars == other.chars &&
         self.extent.row == other.extent.row &&
         self.extent.column == other.extent.column;
}

#endif
