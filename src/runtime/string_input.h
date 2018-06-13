#ifndef RUNTIME_STRING_INPUT_H_
#define RUNTIME_STRING_INPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

typedef struct {
  const char *string;
  uint32_t position;
  uint32_t length;
  TSInput input;
} TSStringInput;

void ts_string_input_init(TSStringInput *, const char *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STRING_INPUT_H_
