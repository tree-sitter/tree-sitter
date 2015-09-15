#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include "tree_sitter/runtime.h"
#include <stdbool.h>

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  TSLength result;
  result.bytes = len1.bytes + len2.bytes;
  result.chars = len1.chars + len2.chars;

  if ((len1.chars > 0 && len1.bytes == 0) || (len2.chars > 0 && len2.bytes == 0))
    result.bytes = 0;

  return result;
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  TSLength result;
  result.bytes = len1.bytes - len2.bytes;
  result.chars = len1.chars - len2.chars;

  if ((len1.chars > 0 && len1.bytes == 0) || (len2.chars > 0 && len2.bytes == 0))
    result.bytes = 0;

  return result;
}

static inline TSLength ts_length_zero() {
  TSLength result;
  result.bytes = result.chars = 0;
  return result;
}

static inline bool ts_length_eq(TSLength len1, TSLength len2) {
  return len1.bytes == len2.bytes && len1.chars == len2.chars;
}

static inline TSLength ts_length_make(size_t bytes, size_t chars) {
  TSLength result;
  result.bytes = bytes;
  result.chars = chars;
  return result;
}

#endif
