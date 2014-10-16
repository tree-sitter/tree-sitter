#ifndef RUNTIME_DEBUGGER_H_
#define RUNTIME_DEBUGGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

static inline TSDebugger ts_debugger_null() {
  TSDebugger debugger = { 0, 0, 0 };
  return debugger;
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_DEBUGGER_H_
