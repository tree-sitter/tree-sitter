#ifndef TREE_SITTER_UNICODE_H_
#define TREE_SITTER_UNICODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef ptrdiff_t ssize_t;

typedef ssize_t (*DecodeNextFunction)(
  const uint8_t *,
  size_t,
  uint32_t *
);

typedef enum {
  DECODE_NEXT_ERROR = -1,
  DECODE_NEXT_OK = 0
} DecodeNextResult;

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_UNICODE_H_
