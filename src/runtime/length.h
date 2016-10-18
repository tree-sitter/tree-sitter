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
} TSLength;

static inline bool ts_length_has_unknown_chars(TSLength self) {
  return self.bytes > 0 && self.chars == 0;
}

static inline void ts_length_set_unknown_chars(TSLength *self) {
  self->chars = 0;
}

static inline TSLength ts_length_min(TSLength len1, TSLength len2) {
  return (len1.chars < len2.chars) ? len1 : len2;
}

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  TSLength result;
  result.chars = len1.chars + len2.chars;
  result.bytes = len1.bytes + len2.bytes;
  result.extent = ts_point_add(len1.extent, len2.extent);

  if (ts_length_has_unknown_chars(len1) || ts_length_has_unknown_chars(len2)) {
    result.chars = 0;
  } else {
    result.chars = len1.chars + len2.chars;
  }

  return result;
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  TSLength result;
  result.bytes = len1.bytes - len2.bytes;
  result.extent = ts_point_sub(len1.extent, len2.extent);

  if (ts_length_has_unknown_chars(len1) || ts_length_has_unknown_chars(len2)) {
    result.chars = 0;
  } else {
    result.chars = len1.chars - len2.chars;
  }

  return result;
}

static inline TSLength ts_length_zero() {
  return (TSLength){ 0, 0, {0, 0} };
}

static inline bool ts_length_eq(TSLength self, TSLength other) {
  return self.bytes == other.bytes && self.chars == other.chars &&
         self.extent.row == other.extent.row &&
         self.extent.column == other.extent.column;
}

#endif
