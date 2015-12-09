#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"
#include "runtime/vector.h"

typedef struct {
  TSLexer lexer;
  Stack *stack;
  const TSLanguage *language;
  Vector lookahead_states;
  Vector reduce_parents;
  int finished_stack_head;
} TSParser;

TSParser ts_parser_make();
void ts_parser_destroy(TSParser *);
TSDebugger ts_parser_debugger(const TSParser *);
void ts_parser_set_debugger(TSParser *, TSDebugger);
TSTree *ts_parser_parse(TSParser *, TSInput, TSTree *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
