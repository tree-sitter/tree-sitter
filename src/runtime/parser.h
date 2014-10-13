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
  TSDebugger debugger;
} TSParser;

TSParser ts_parser_make();
void ts_parser_destroy(TSParser *);
void ts_parser_debug_parse(TSParser *, TSDebugger);
void ts_parser_debug_lex(TSParser *, TSDebugger);
const TSTree *ts_parser_parse(TSParser *, TSInput, TSInputEdit *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
