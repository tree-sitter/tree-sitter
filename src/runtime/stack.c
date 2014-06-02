#include "tree_sitter/runtime.h"
#include "tree_sitter/parser/stack.h"
#include <string.h>

static size_t INITIAL_STACK_SIZE = 100;
static ts_state_id INITIAL_STATE = 0;

ts_stack ts_stack_make() {
    ts_stack result = {
        .entries = calloc(INITIAL_STACK_SIZE, sizeof(*result.entries)),
        .size = 0,
    };
    return result;
}

ts_state_id ts_stack_top_state(const ts_stack *stack) {
    if (stack->size == 0) return INITIAL_STATE;
    return stack->entries[stack->size - 1].state;
}

ts_tree * ts_stack_top_node(const ts_stack *stack) {
    if (stack->size == 0) return NULL;
    return stack->entries[stack->size - 1].node;
}

void ts_stack_push(ts_stack *stack, ts_state_id state, ts_tree *node) {
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

ts_tree * ts_stack_reduce(ts_stack *stack,
                          ts_symbol symbol,
                          size_t immediate_child_count,
                          const int *hidden_symbol_flags,
                          const int *ubiquitous_symbol_flags) {

    // First, walk down the stack to determine which symbols will be reduced.
    // The child node count is known ahead of time, but some of the
    // nodes at the top of the stack might be hidden nodes, in which
    // case we 'collapse' them. Some may also be ubiquitous tokens,
    // which don't count towards the child node count.
    static int collapse_flags[100];
    int child_count = 0;
    for (size_t i = 0; i < immediate_child_count; i++) {
        size_t stack_index = stack->size - 1 - i;
        ts_tree *child = stack->entries[stack_index].node;
        size_t grandchild_count;
        ts_tree **grandchildren = ts_tree_children(child, &grandchild_count);
        ts_symbol child_symbol = ts_tree_symbol(child);

        collapse_flags[i] = (
            hidden_symbol_flags[child_symbol] ||
            (grandchild_count == 1 && ts_tree_size(child) == ts_tree_size(grandchildren[0]))
        );

        child_count += collapse_flags[i] ? grandchild_count : 1;

        if (ubiquitous_symbol_flags && ubiquitous_symbol_flags[child_symbol])
            immediate_child_count++;
    }

    // Walk down the stack again, building up the array of children.
    // Though we collapse the hidden child nodes, we also need to
    // keep track of the actual immediate children so that we can
    // later collapse the stack again when the document is edited.
    // We store the children and immediate children in the same array,
    // to reduce allocations.
    size_t child_index = child_count;
    ts_tree **children = malloc((child_count + immediate_child_count) * sizeof(ts_tree *));
    ts_tree **immediate_children = children + child_count;

    for (size_t i = 0; i < immediate_child_count; i++) {
        ts_tree *child = stack->entries[stack->size - 1 - i].node;
        immediate_children[immediate_child_count - 1 - i] = child;

        if (collapse_flags[i]) {
            size_t grandchild_count;
            ts_tree **grandchildren = ts_tree_children(child, &grandchild_count);
            child_index -= grandchild_count;
            memcpy(children + child_index, grandchildren, (grandchild_count * sizeof(ts_tree *)));
        } else {
            child_index--;
            children[child_index] = child;
        }
    }

    ts_tree *lookahead = ts_tree_make_node(symbol, child_count, immediate_child_count, children);
    ts_stack_shrink(stack, stack->size - immediate_child_count);
    return lookahead;
}
