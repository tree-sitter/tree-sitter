#ifndef RUNTIME_ATOMIC_H_
#define RUNTIME_ATOMIC_H_

#include <stdint.h>

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
  return __sync_add_and_fetch(p, 1u);
}

static inline uint32_t atomic_dec(volatile uint32_t *p) {
  return __sync_sub_and_fetch(p, 1u);
}

#endif

#endif  // RUNTIME_ATOMIC_H_
