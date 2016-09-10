#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include "tree_sitter/parser.h"
#include <stdbool.h>

static inline TSPoint ts_point_add(TSPoint a, TSPoint b) {
  if (b.row > 0)
    return (TSPoint){a.row + b.row, b.column};
  else
    return (TSPoint){a.row, a.column + b.column};
}

static inline TSPoint ts_point_sub(TSPoint a, TSPoint b) {
  if (a.row > b.row)
    return (TSPoint){a.row - b.row, a.column};
  else
    return (TSPoint){0, a.column - b.column};
}

static inline bool ts_length_is_unknown(TSLength self) {
  return self.chars > 0 && self.bytes == 0;
}

static inline void ts_length_set_unknown(TSLength *self) {
  self->bytes = 0;
  self->extent = (TSPoint){0, 0};
}

static inline TSLength ts_length_min(TSLength len1, TSLength len2) {
  return (len1.chars < len2.chars) ? len1 : len2;
}

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  TSLength result;
  result.chars = len1.chars + len2.chars;

  if (ts_length_is_unknown(len1) || ts_length_is_unknown(len2)) {
    result.bytes = 0;
    result.extent = (TSPoint){0, result.chars};
  } else {
    result.bytes = len1.bytes + len2.bytes;
    result.extent = ts_point_add(len1.extent, len2.extent);
  }

  return result;
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  TSLength result;
  result.chars = len1.chars - len2.chars;

  if (ts_length_is_unknown(len1) || ts_length_is_unknown(len2)) {
    result.bytes = 0;
    result.extent = (TSPoint){0, result.chars};
  } else {
    result.bytes = len1.bytes - len2.bytes;
    result.extent = ts_point_sub(len1.extent, len2.extent);
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
