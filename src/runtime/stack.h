#ifndef RUNTIME_STACK_H_
#define RUNTIME_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

typedef struct {
  TSTree *node;
  TSStateId state;
} TSStackEntry;

typedef struct {
  size_t size;
  size_t capacity;
  TSStackEntry *entries;
} TSStack;

TSStack ts_stack_make();
void ts_stack_delete(TSStack *);
void ts_stack_shrink(TSStack *stack, size_t new_size);
void ts_stack_push(TSStack *stack, TSStateId state, TSTree *node);
TSStateId ts_stack_top_state(const TSStack *stack);
TSTree *ts_stack_top_node(const TSStack *stack);
TSLength ts_stack_total_tree_size(const TSStack *stack);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STACK_H_
