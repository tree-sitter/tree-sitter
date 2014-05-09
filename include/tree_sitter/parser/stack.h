#ifndef TREE_SITTER_PARSER_STACK_H_
#define TREE_SITTER_PARSER_STACK_H_

#include "tree_sitter/runtime.h"

typedef unsigned short ts_state_id;

typedef struct {
    size_t size;
    struct {
        ts_tree *node;
        ts_state_id state;
    } *entries;
} ts_stack;

ts_stack ts_stack_make();
ts_tree * ts_stack_reduce(ts_stack *stack, ts_symbol symbol, size_t immediate_child_count, const int *hidden_symbol_flags, const int *ubiquitous_symbol_flags);
void ts_stack_shrink(ts_stack *stack, size_t new_size);
void ts_stack_push(ts_stack *stack, ts_state_id state, ts_tree *node);
ts_state_id ts_stack_top_state(const ts_stack *stack);
ts_tree * ts_stack_top_node(const ts_stack *stack);
size_t ts_stack_right_position(const ts_stack *stack);

#endif