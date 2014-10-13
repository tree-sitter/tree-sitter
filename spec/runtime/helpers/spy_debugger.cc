#include "runtime/helpers/spy_debugger.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

static void spy_debug(void *data, const char *msg) {
  SpyDebugger *debugger = static_cast<SpyDebugger *>(data);
  debugger->messages.push_back(msg);
}

static void spy_release(void *data) {
  SpyDebugger *debugger = static_cast<SpyDebugger *>(data);
  debugger->release_call_count++;
}

TSDebugger SpyDebugger::debugger() {
  TSDebugger result;
  result.data = (void *)this;
  result.debug_fn = spy_debug;
  result.release_fn = spy_release;
  return result;
}

void SpyDebugger::clear() {
  messages.clear();
}
