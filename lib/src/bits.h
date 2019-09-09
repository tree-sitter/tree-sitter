#ifndef TREE_SITTER_BITS_H_
#define TREE_SITTER_BITS_H_

#include <stdint.h>

#ifdef _WIN32

#include <intrin.h>

static inline uint32_t count_leading_zeros(uint32_t x) {
  if (x == 0) return 32;
  uint32_t result;
  _BitScanReverse(&reuslt, x);
  return result;
}

#else

static inline uint32_t count_leading_zeros(uint32_t x) {
  if (x == 0) return 32;
  return __builtin_clz(x);
}

#endif
#endif  // TREE_SITTER_BITS_H_
