#ifndef TREE_SITTER_PARSER_STACK_H_
#define TREE_SITTER_PARSER_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/runtime.h"

typedef unsigned short ts_state_id;

typedef struct {
    size_t size;
    struct {
        TSTree *node;
        ts_state_id state;
        int is_extra;
    } *entries;
} ts_stack;

ts_stack ts_stack_make();
void ts_stack_delete(ts_stack *);
TSTree * ts_stack_reduce(ts_stack *stack, ts_symbol symbol, size_t immediate_child_count, const int *hidden_symbol_flags, int gather_extras);
void ts_stack_shrink(ts_stack *stack, size_t new_size);
void ts_stack_push(ts_stack *stack, ts_state_id state, TSTree *node);
ts_state_id ts_stack_top_state(const ts_stack *stack);
TSTree * ts_stack_top_node(const ts_stack *stack);
size_t ts_stack_right_position(const ts_stack *stack);

#ifdef __cplusplus
}
#endif

#endif
