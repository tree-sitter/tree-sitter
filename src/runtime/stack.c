#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/stack.h"

static size_t INITIAL_SIZE = 100;
static TSStateId INITIAL_STATE = 0;

TSStack ts_stack_make() {
  return (TSStack) { .size = 0,
                     .capacity = INITIAL_SIZE,
                     .entries = malloc(INITIAL_SIZE * sizeof(TSStackEntry)) };
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
  if (stack->size == stack->capacity) {
    stack->capacity *= 2;
    stack->entries =
        realloc(stack->entries, stack->capacity * sizeof(*stack->entries));
  }
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
