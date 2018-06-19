#include "runtime/subtree.h"

typedef struct {
  const Subtree *tree;
  uint32_t child_index;
  uint32_t byte_offset;
} StackEntry;

typedef struct {
  Array(StackEntry) stack;
  const Subtree *last_external_token;
} ReusableNode;

static inline ReusableNode reusable_node_new() {
  return (ReusableNode) {array_new(), NULL};
}

static inline void reusable_node_clear(ReusableNode *self) {
  array_clear(&self->stack);
  self->last_external_token = NULL;
}

static inline void reusable_node_reset(ReusableNode *self, const Subtree *tree) {
  reusable_node_clear(self);
  array_push(&self->stack, ((StackEntry) {
    .tree = tree,
    .child_index = 0,
    .byte_offset = 0,
  }));
}

static inline const Subtree *reusable_node_tree(ReusableNode *self) {
  return self->stack.size > 0
    ? self->stack.contents[self->stack.size - 1].tree
    : NULL;
}

static inline uint32_t reusable_node_byte_offset(ReusableNode *self) {
  return self->stack.size > 0
    ? self->stack.contents[self->stack.size - 1].byte_offset
    : UINT32_MAX;
}

static inline void reusable_node_delete(ReusableNode *self) {
  array_delete(&self->stack);
}

static inline void reusable_node_advance(ReusableNode *self) {
  StackEntry last_entry = *array_back(&self->stack);
  uint32_t byte_offset = last_entry.byte_offset + ts_subtree_total_bytes(last_entry.tree);
  if (last_entry.tree->has_external_tokens) {
    self->last_external_token = ts_subtree_last_external_token(last_entry.tree);
  }

  const Subtree *tree;
  uint32_t next_index;
  do {
    StackEntry popped_entry = array_pop(&self->stack);
    next_index = popped_entry.child_index + 1;
    if (self->stack.size == 0) return;
    tree = array_back(&self->stack)->tree;
  } while (tree->children.size <= next_index);

  array_push(&self->stack, ((StackEntry) {
    .tree = tree->children.contents[next_index],
    .child_index = next_index,
    .byte_offset = byte_offset,
  }));
}

static inline bool reusable_node_descend(ReusableNode *self) {
  StackEntry last_entry = *array_back(&self->stack);
  if (last_entry.tree->children.size > 0) {
    array_push(&self->stack, ((StackEntry) {
      .tree = last_entry.tree->children.contents[0],
      .child_index = 0,
      .byte_offset = last_entry.byte_offset,
    }));
    return true;
  } else {
    return false;
  }
}

static inline void reusable_node_advance_past_leaf(ReusableNode *self) {
  while (reusable_node_descend(self)) {}
  reusable_node_advance(self);
}
