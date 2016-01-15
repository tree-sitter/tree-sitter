#include "helpers/spy_debugger.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

static void spy_debug(void *data, TSDebugType type, const char *msg) {
  SpyDebugger *debugger = static_cast<SpyDebugger *>(data);
  debugger->messages.push_back(msg);
}

TSDebugger SpyDebugger::debugger() {
  TSDebugger result;
  result.payload = (void *)this;
  result.debug_fn = spy_debug;
  return result;
}

void SpyDebugger::clear() {
  messages.clear();
}
