#include "runtime/tree.h"

typedef struct {
  Tree *tree;
  uint32_t byte_index;
  Tree *preceding_external_token;
} ReusableNode;

static inline ReusableNode reusable_node_new(Tree *tree) {
  ReusableNode result = {tree, 0, NULL};
  return result;
}

static inline void reusable_node_pop(ReusableNode *self) {
  self->byte_index += ts_tree_total_bytes(self->tree);
  if (self->tree->has_external_tokens) {
    self->preceding_external_token = ts_tree_last_external_token(self->tree);
  }

  while (self->tree) {
    Tree *parent = self->tree->context.parent;
    uint32_t next_index = self->tree->context.index + 1;
    if (parent && parent->child_count > next_index) {
      self->tree = parent->children[next_index];
      return;
    }
    self->tree = parent;
  }
}

static inline void reusable_node_pop_leaf(ReusableNode *self) {
  while (self->tree->child_count > 0)
    self->tree = self->tree->children[0];
  reusable_node_pop(self);
}

static inline bool reusable_node_breakdown(ReusableNode *self) {
  if (self->tree->child_count == 0) {
    return false;
  } else {
    self->tree = self->tree->children[0];
    return true;
  }
}
