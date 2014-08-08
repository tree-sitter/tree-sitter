#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/stack.h"

static size_t INITIAL_STACK_SIZE = 100;
static TSStateId INITIAL_STATE = 0;

TSStack ts_stack_make() {
  TSStack result = {
    .entries = calloc(INITIAL_STACK_SIZE, sizeof(*result.entries)), .size = 0,
  };
  return result;
}

void ts_stack_delete(TSStack *stack) {
  ts_stack_shrink(stack, 0);
  free(stack->entries);
}

TSStateId ts_stack_top_state(const TSStack *stack) {
  if (stack->size == 0)
    return INITIAL_STATE;
  return stack->entries[stack->size - 1].state;
}

TSTree *ts_stack_top_node(const TSStack *stack) {
  if (stack->size == 0)
    return NULL;
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

TSTree *ts_stack_reduce(TSStack *stack, TSSymbol symbol, size_t child_count,
                        const int *hidden_symbol_flags) {

  // First, walk down the stack to determine which symbols will be reduced.
  // The child node count is known ahead of time, but some children may be
  // ubiquitous tokens, which don't count.
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = stack->entries[stack->size - 1 - i].node;
    if (ts_tree_is_extra(child))
      child_count++;
  }

  size_t start_index = stack->size - child_count;
  TSTree **children = calloc(child_count, sizeof(TSTree *));
  for (size_t i = 0; i < child_count; i++)
    children[i] = stack->entries[start_index + i].node;

  TSTree *lookahead = ts_tree_make_node(symbol, child_count, children,
                                        hidden_symbol_flags[symbol]);
  ts_stack_shrink(stack, stack->size - child_count);
  return lookahead;
}
