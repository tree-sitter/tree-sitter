#ifndef TREE_SITTER_CLOCK_H_
#define TREE_SITTER_CLOCK_H_

#include <stdint.h>

#ifdef _WIN32

#include <windows.h>

static inline uint64_t get_clock() {
  LARGE_INTEGER result;
  QueryPerformanceCounter(&result);
  return (uint64_t)result.QuadPart;
}

static inline uint64_t get_clocks_per_second() {
  LARGE_INTEGER result;
  QueryPerformanceFrequency(&result);
  return (uint64_t)result.QuadPart;
}

#else

static inline uint64_t get_clock() {
  return (uint64_t)clock();
}

static inline uint64_t get_clocks_per_second() {
  return (uint64_t)CLOCKS_PER_SEC;
}

#endif

#endif  // TREE_SITTER_CLOCK_H_
