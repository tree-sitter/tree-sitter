#include "tree_sitter/runtime.h"
#include <stdio.h>

static void log_debug(void *payload, TSDebugType type, const char *msg) {
  bool include_lexing = (bool)payload;
  switch (type) {
    case TSDebugTypeParse:
      fprintf(stderr, "* %s\n", msg);
      break;
    case TSDebugTypeLex:
      if (include_lexing)
        fprintf(stderr, "  %s\n", msg);
      break;
  }
}

TSDebugger log_debugger_make(bool include_lexing) {
  TSDebugger result;
  result.payload = (void *)include_lexing;
  result.debug_fn = log_debug;
  return result;
}
