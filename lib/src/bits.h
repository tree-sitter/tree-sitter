#ifndef TREE_SITTER_BITS_H_
#define TREE_SITTER_BITS_H_

#include <stdint.h>

static inline uint32_t bitmask_for_index(uint16_t id) {
  return (1u << (31 - id));
}

#ifdef __TINYC__

// Algorithm taken from the Hacker's Delight book
// See also https://graphics.stanford.edu/~seander/bithacks.html
static inline uint32_t count_leading_zeros(uint32_t x) {
  int count = 0;
  if (x == 0) return 32;
  x = x - ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  count = (((x + (x >> 4)) & 0x0f0f0f0f) * 0x01010101) >> 24;
  return count;
}

#elif defined _WIN32 && !defined __GNUC__

#include <intrin.h>

static inline uint32_t count_leading_zeros(uint32_t x) {
  if (x == 0) return 32;
  uint32_t result;
  _BitScanReverse(&result, x);
  return 31 - result;
}

#else

static inline uint32_t count_leading_zeros(uint32_t x) {
  if (x == 0) return 32;
  return __builtin_clz(x);
}

#endif
#endif  // TREE_SITTER_BITS_H_
