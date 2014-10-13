#ifndef HELPERS_SPY_DEBUGGER_H_
#define HELPERS_SPY_DEBUGGER_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyDebugger {
 public:
  void clear();
  TSDebugger debugger();

  std::vector<std::string> messages;
  size_t release_call_count;
};

#endif  // HELPERS_SPY_DEBUGGER_H_

