#ifndef RUNTIME_DEBUGGER_H_
#define RUNTIME_DEBUGGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

static inline TSDebugger ts_debugger_null() {
  return (TSDebugger) { .data = NULL, .debug_fn = NULL, .release_fn = NULL, };
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_DEBUGGER_H_
