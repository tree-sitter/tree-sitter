#include "tree_sitter/runtime.h"
#include <stdio.h>

static void log_debug(void *data, TSDebugType type, const char *msg) {
  switch (type) {
    case TSDebugTypeParse:
      fprintf(stderr, "* %s\n", msg);
      break;
    case TSDebugTypeLex:
      fprintf(stderr, "  %s\n", msg);
      break;
  }
}

TSDebugger log_debugger_make() {
  TSDebugger result;
  result.payload = NULL;
  result.debug_fn = log_debug;
  return result;
}
