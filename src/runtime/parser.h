#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"
#include "runtime/parse_stack.h"

typedef struct {
  TSLexer lexer;
  ParseStack *stack;
  TSStack right_stack;
  size_t total_chars;
  TSTree *lookahead;
  const TSLanguage *language;
} TSParser;

TSParser ts_parser_make();
void ts_parser_destroy(TSParser *);
TSDebugger ts_parser_debugger(const TSParser *);
void ts_parser_set_debugger(TSParser *, TSDebugger);
TSTree *ts_parser_parse(TSParser *, TSInput, TSInputEdit *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
