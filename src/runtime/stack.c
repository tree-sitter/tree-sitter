#include "tree_sitter/runtime.h"
#include "tree_sitter/parser/stack.h"
#include "runtime/tree.h"
#include <string.h>

static size_t INITIAL_STACK_SIZE = 100;
static TSStateId INITIAL_STATE = 0;

TSStack ts_stack_make() {
    TSStack result = {
        .entries = calloc(INITIAL_STACK_SIZE, sizeof(*result.entries)),
        .size = 0,
    };
    return result;
}

void ts_stack_delete(TSStack *stack) {
    ts_stack_shrink(stack, 0);
    free(stack->entries);
}

TSStateId ts_stack_top_state(const TSStack *stack) {
    if (stack->size == 0) return INITIAL_STATE;
    return stack->entries[stack->size - 1].state;
}

TSTree * ts_stack_top_node(const TSStack *stack) {
    if (stack->size == 0) return NULL;
    return stack->entries[stack->size - 1].node;
}

void ts_stack_push(TSStack *stack, TSStateId state, TSTree *node) {
    stack->entries[stack->size].state = state;
    stack->entries[stack->size].node = node;
    stack->size++;
    ts_tree_retain(node);
}

void ts_stack_shrink(TSStack *stack, size_t new_size) {
    for (size_t i = new_size; i < stack->size; i++)
        ts_tree_release(stack->entries[i].node);
    stack->size = new_size;
}

size_t ts_stack_right_position(const TSStack *stack) {
    size_t result = 0;
    for (size_t i = 0; i < stack->size; i++) {
        TSTree *node = stack->entries[i].node;
        result += ts_tree_total_size(node);
    }
    return result;
}

TSTree * ts_stack_reduce(TSStack *stack,
                          TSSymbol symbol,
                          size_t immediate_child_count,
                          const int *hidden_symbol_flags,
                          int gather_extra) {

    // First, walk down the stack to determine which symbols will be reduced.
    // The child node count is known ahead of time, but some of the
    // nodes at the top of the stack might be hidden nodes, in which
    // case we 'collapse' them. Some may also be extra tokens,
    // which don't count towards the child node count.
    static int collapse_flags[100];
    int child_count = 0;
    for (size_t i = 0; i < immediate_child_count; i++) {
        size_t stack_index = stack->size - 1 - i;
        TSTree *child = stack->entries[stack_index].node;
        size_t grandchild_count;
        TSTree **grandchildren = ts_tree_children(child, &grandchild_count);
        TSSymbol child_symbol = ts_tree_symbol(child);

        collapse_flags[i] = (
            hidden_symbol_flags[child_symbol] ||
            (grandchild_count == 1 && ts_tree_size(child) == ts_tree_size(grandchildren[0]))
        );

        child_count += collapse_flags[i] ? grandchild_count : 1;

        if (gather_extra && child->is_extra)
            immediate_child_count++;
    }

    // Walk down the stack again, building up the array of children.
    // Though we collapse the hidden child nodes, we also need to
    // keep track of the actual immediate children so that we can
    // later collapse the stack again when the document is edited.
    // We store the children and immediate children in the same array,
    // to reduce allocations.
    size_t child_index = child_count;
    TSTree **children = malloc((child_count + immediate_child_count) * sizeof(TSTree *));
    TSTree **immediate_children = children + child_count;

    for (size_t i = 0; i < immediate_child_count; i++) {
        TSTree *child = stack->entries[stack->size - 1 - i].node;
        immediate_children[immediate_child_count - 1 - i] = child;

        if (collapse_flags[i]) {
            size_t grandchild_count;
            TSTree **grandchildren = ts_tree_children(child, &grandchild_count);
            child_index -= grandchild_count;
            memcpy(children + child_index, grandchildren, (grandchild_count * sizeof(TSTree *)));
        } else {
            child_index--;
            children[child_index] = child;
        }
    }

    TSTree *lookahead = ts_tree_make_node(symbol, child_count, immediate_child_count, children);
    ts_stack_shrink(stack, stack->size - immediate_child_count);
    return lookahead;
}
