#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"
#include "runtime/array.h"
#include "runtime/reduce_action.h"

typedef struct {
  TSLexer lexer;
  Stack *stack;
  const TSLanguage *language;
  ReduceActionSet reduce_actions;
  TSTree *finished_tree;
  bool is_split;
  bool print_debugging_graphs;
  TSTree scratch_tree;
} TSParser;

bool ts_parser_init(TSParser *);
void ts_parser_destroy(TSParser *);
TSTree *ts_parser_parse(TSParser *, TSInput, TSTree *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
