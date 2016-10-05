#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  size_t bytes;
  size_t chars;
  size_t rows;
  size_t columns;
} TSLength;

static inline bool ts_length_is_unknown(TSLength self) {
  return self.chars > 0 && self.bytes == 0;
}

static inline void ts_length_set_unknown(TSLength *self) {
  self->bytes = 0;
  self->rows = 0;
  self->columns = 0;
}

static inline TSLength ts_length_min(TSLength len1, TSLength len2) {
  return (len1.chars < len2.chars) ? len1 : len2;
}

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  TSLength result;
  result.chars = len1.chars + len2.chars;

  if (ts_length_is_unknown(len1) || ts_length_is_unknown(len2)) {
    result.bytes = 0;
    result.rows = 0;
    result.columns = result.chars;
  } else {
    result.bytes = len1.bytes + len2.bytes;
    if (len2.rows == 0) {
      result.rows = len1.rows;
      result.columns = len1.columns + len2.columns;
    } else {
      result.rows = len1.rows + len2.rows;
      result.columns = len2.columns;
    }
  }

  return result;
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  TSLength result;
  result.chars = len1.chars - len2.chars;

  if (ts_length_is_unknown(len1) || ts_length_is_unknown(len2)) {
    result.bytes = 0;
    result.rows = 0;
    result.columns = result.chars;
  } else {
    result.bytes = len1.bytes - len2.bytes;
    if (len1.rows == len2.rows) {
      result.rows = 0;
      result.columns = len1.columns - len2.columns;
    } else {
      result.rows = len1.rows - len2.rows;
      result.columns = len1.columns;
    }
  }

  return result;
}

static inline TSLength ts_length_zero() {
  return (TSLength){ 0, 0, 0, 0 };
}

static inline bool ts_length_eq(TSLength self, TSLength other) {
  return self.bytes == other.bytes && self.chars == other.chars &&
         self.rows == other.rows && self.columns == other.columns;
}

#endif
