#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"

typedef struct {
  TSLexer lexer;
  TSStack stack;
  TSStack right_stack;
  size_t total_chars;
  TSTree *lookahead;
  TSTree *next_lookahead;
  const TSLanguage *language;
} TSParser;

TSParser ts_parser_make();
void ts_parser_destroy(TSParser *);
TSDebugger ts_parser_get_debugger(const TSParser *);
void ts_parser_set_debugger(TSParser *, TSDebugger);
const TSTree *ts_parser_parse(TSParser *, TSInput, TSInputEdit *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
