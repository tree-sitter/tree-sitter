#ifndef RUNTIME_UTF16_H_
#define RUNTIME_UTF16_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

// Analogous to utf8proc's utf8proc_iterate function. Reads one code point from
// the given string and stores it in the location pointed to by `code_point`.
// Returns the number of bytes in `string` that were read.
int utf16_iterate(const uint8_t *string, size_t length, int32_t *code_point);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_UTF16_H_
