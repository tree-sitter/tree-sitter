#ifndef RUNTIME_PARSE_STACK_H_
#define RUNTIME_PARSE_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

typedef struct ParseStack ParseStack;

typedef struct ParseStackNode {
  TSTree *tree;
  TSStateId state;
  struct ParseStackNode *successors[4];
  short unsigned int successor_count;
  short unsigned int ref_count;
} ParseStackNode;

ParseStack *ts_parse_stack_new();
void ts_parse_stack_delete(ParseStack *);

ParseStackNode *ts_parse_stack_head(const ParseStack *, int);
int ts_parse_stack_head_count(const ParseStack *);

bool ts_parse_stack_shift(ParseStack *, int, TSStateId, TSTree *);
bool ts_parse_stack_reduce(ParseStack *, int, TSStateId, TSSymbol, int);
int ts_parse_stack_split(ParseStack *, int);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSE_STACK_H_
