#ifndef RUNTIME_ATOMIC_H_
#define RUNTIME_ATOMIC_H_

#ifdef _WIN32

#include <windows.h>

static inline uint32_t atomic_inc(volatile uint32_t *p) {
  return InterlockedIncrement(p);
}

static inline uint32_t atomic_dec(volatile uint32_t *p) {
  return InterlockedDecrement(p);
}

#else

static inline uint32_t atomic_inc(volatile uint32_t *p) {
  return __sync_fetch_and_add(p, 1u) + 1;
}

static inline uint32_t atomic_dec(volatile uint32_t *p) {
  return __sync_fetch_and_sub(p, 1u) - 1;
}

#endif

#endif  // RUNTIME_ATOMIC_H_
