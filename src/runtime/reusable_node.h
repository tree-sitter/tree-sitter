#include "runtime/tree.h"

typedef struct {
  Tree *tree;
  uint32_t byte_index;
  Tree *last_external_token;
} ReusableNode;

static inline ReusableNode reusable_node_new(Tree *tree) {
  ReusableNode result = {tree, 0, NULL};
  return result;
}

static inline void reusable_node_pop(ReusableNode *self) {
  self->byte_index += ts_tree_total_bytes(self->tree);
  if (self->tree->has_external_tokens) {
    self->last_external_token = ts_tree_last_external_token(self->tree);
  }

  while (self->tree) {
    Tree *parent = self->tree->context.parent;
    uint32_t next_index = self->tree->context.index + 1;
    if (parent && parent->children.size > next_index) {
      self->tree = parent->children.contents[next_index];
      return;
    }
    self->tree = parent;
  }
}

static inline ReusableNode reusable_node_after_leaf(const ReusableNode *self) {
  ReusableNode result = *self;
  while (result.tree->children.size > 0)
    result.tree = result.tree->children.contents[0];
  reusable_node_pop(&result);
  return result;
}

static inline bool reusable_node_breakdown(ReusableNode *self) {
  if (self->tree->children.size == 0) {
    return false;
  } else {
    self->tree = self->tree->children.contents[0];
    return true;
  }
}
