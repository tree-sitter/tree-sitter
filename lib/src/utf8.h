#ifndef TREE_SITTER_UTF8_H_
#define TREE_SITTER_UTF8_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#include "./unicode.h"

/**
 * Decode next UTF-8 encoded code point
 *
 * Attempts to decode a single code point given an input sequence of UTF-8
 * encoded code units. The start of the input sequence, `str`, should be on a
 * code point boundary. Up to `length` bytes from `str` are read. On success,
 * the number of bytes read is returned; on failure or for invalid input
 * sequences, `DECODE_NEXT_ERROR` is returned. The decoded code point is placed
 * in the output parameter `code_point`.
 */
ssize_t utf8_decode_next(const uint8_t *str, size_t length, uint32_t *code_point);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_UTF8_H_
