#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"

typedef struct {
  TSLexer lexer;
  TSStack stack;
  int debug;
  TSTree *lookahead;
  TSTree *next_lookahead;
  const TSLanguage *language;
} TSParser;

TSParser ts_parser_make(const TSLanguage *);
void ts_parser_destroy(TSParser *);
const TSTree *ts_parser_parse(TSParser *, TSInput, TSInputEdit *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
