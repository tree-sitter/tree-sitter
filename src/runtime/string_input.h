#ifndef RUNTIME_STRING_INPUT_H_
#define RUNTIME_STRING_INPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

TSInput ts_string_input_make(const char *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STRING_INPUT_H_
