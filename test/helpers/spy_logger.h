#ifndef HELPERS_SPY_LOGGER_H_
#define HELPERS_SPY_LOGGER_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyLogger {
 public:
  void clear();
  TSLogger logger();
  std::vector<std::string> messages;
};

#endif  // HELPERS_SPY_DEBUGGER_H_
