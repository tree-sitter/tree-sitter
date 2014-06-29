#ifndef TREE_SITTER_PARSER_STACK_H_
#define TREE_SITTER_PARSER_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

typedef unsigned short TSStateId;

typedef struct {
    size_t size;
    struct {
        TSTree *node;
        TSStateId state;
        int is_extra;
    } *entries;
} TSStack;

TSStack ts_stack_make();
void ts_stack_delete(TSStack *);
TSTree * ts_stack_reduce(TSStack *stack, TSSymbol symbol, size_t immediate_child_count, const int *hidden_symbol_flags, int gather_extras);
void ts_stack_shrink(TSStack *stack, size_t new_size);
void ts_stack_push(TSStack *stack, TSStateId state, TSTree *node);
TSStateId ts_stack_top_state(const TSStack *stack);
TSTree * ts_stack_top_node(const TSStack *stack);
size_t ts_stack_right_position(const TSStack *stack);

#ifdef __cplusplus
}
#endif

#endif
