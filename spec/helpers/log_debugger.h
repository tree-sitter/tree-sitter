#ifndef HELPERS_LOG_DEBUGGER_H_
#define HELPERS_LOG_DEBUGGER_H_

#include "tree_sitter/runtime.h"

TSDebugger log_debugger_make(bool include_lexing);

#endif  // HELPERS_LOG_DEBUGGER_H_
