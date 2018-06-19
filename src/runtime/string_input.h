#ifndef RUNTIME_STRING_INPUT_H_
#define RUNTIME_STRING_INPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

typedef struct {
  const char *string;
  uint32_t length;
} TSStringInput;

void ts_string_input_init(TSStringInput *, const char *, uint32_t);
TSInput ts_string_input_get(TSStringInput *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STRING_INPUT_H_
