#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include "tree_sitter/runtime.h"
#include <stdbool.h>

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  return (TSLength) {
    .bytes = len1.bytes + len2.bytes,
    .chars = len1.chars + len2.chars,
  };
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  return (TSLength) {
    .bytes = len1.bytes - len2.bytes,
    .chars = len1.chars - len2.chars,
  };
}

static inline TSLength ts_length_zero() {
  return (TSLength) { 0, 0 };
}

static inline bool ts_length_eq(TSLength len1, TSLength len2) {
  return len1.bytes == len2.bytes && len1.chars == len2.chars;
}

#endif
