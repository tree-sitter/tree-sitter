#include "tree_sitter/runtime.h"
#include <string.h>

typedef int state_id;
static const state_id ts_lex_state_error = -1;

typedef struct {
    size_t size;
    struct {
        ts_tree *node;
        state_id state;
    } *entries;
} ts_stack;

static int INITIAL_STACK_SIZE = 100;
static int INITIAL_STATE = 0;

ts_stack ts_stack_make() {
    ts_stack result = {
        .entries = calloc(INITIAL_STACK_SIZE, sizeof(*result.entries)),
        .size = 0,
    };
    return result;
}

state_id ts_stack_top_state(const ts_stack *stack) {
    if (stack->size == 0) return INITIAL_STATE;
    return stack->entries[stack->size - 1].state;
}

ts_tree * ts_stack_top_node(const ts_stack *stack) {
    if (stack->size == 0) return NULL;
    return stack->entries[stack->size - 1].node;
}

ts_tree * ts_stack_root(const ts_stack *stack) {
    return stack->entries[0].node;
}

void ts_stack_push(ts_stack *stack, state_id state, ts_tree *node) {
    stack->entries[stack->size].state = state;
    stack->entries[stack->size].node = node;
    stack->size++;
}

void ts_stack_shrink(ts_stack *stack, size_t new_size) {
    for (size_t i = new_size; i < stack->size; i++)
        ts_tree_release(stack->entries[i].node);
    stack->size = new_size;
}

size_t ts_stack_right_position(const ts_stack *stack) {
    size_t result = 0;
    for (size_t i = 0; i < stack->size; i++) {
        ts_tree *node = stack->entries[i].node;
        result += ts_tree_total_size(node);
    }
    return result;
}

ts_tree * ts_stack_reduce(ts_stack *stack, ts_symbol symbol, int child_count, const int *collapse_flags) {
    size_t new_stack_size = stack->size - child_count;

    size_t size = 0, offset = 0;
    ts_tree **children = malloc(child_count * sizeof(ts_tree *));
    for (int i = 0; i < child_count; i++) {
        ts_tree *child = stack->entries[new_stack_size + i].node;
        ts_tree_hide(child, collapse_flags[i]);
        if (i == 0) {
            offset = ts_tree_offset(child);
            size = ts_tree_size(child);
        } else {
            size += ts_tree_total_size(child);
        }

        children[i] = child;
    }

    ts_tree *lookahead = ts_tree_make_node(symbol, child_count, children, size, offset);
    ts_stack_shrink(stack, new_stack_size);
    return lookahead;
}

