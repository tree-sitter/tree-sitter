#include "runtime/node.h"
#include "runtime/tree.h"

TSNode *ts_node_make(const TSTree *tree, TSNode *parent, size_t index,
                     size_t position, const char **names) {
  if (parent)
    ts_node_retain(parent);
  TSNode *result = malloc(sizeof(TSNode));
  *result = (TSNode) { .ref_count = 1,
                       .parent = parent,
                       .index = index,
                       .content = tree,
                       .position = position,
                       .names = names, };
  return result;
}

TSNode *ts_node_make_root(const TSTree *tree, const char **names) {
  return ts_node_make(tree, NULL, 0, 0, names);
}

void ts_node_retain(TSNode *node) { node->ref_count++; }

void ts_node_release(TSNode *node) {
  node->ref_count--;
  if (node->ref_count == 0) {
    if (node->parent)
      ts_node_release(node->parent);
    free(node);
  }
}

size_t ts_node_pos(const TSNode *node) { return node->position; }

size_t ts_node_size(const TSNode *node) { return node->content->size; }

int ts_node_eq(const TSNode *left, const TSNode *right) {
  return ts_tree_equals(left->content, right->content);
}

const char *ts_node_name(const TSNode *node) {
  return node->names[node->content->symbol];
}

const char *ts_node_string(const TSNode *node) {
  return ts_tree_string(node->content, node->names);
}

TSNode *ts_node_parent(TSNode *child) { return child->parent; }

TSNode *ts_node_prev_sibling(TSNode *child) {
  if (child->parent)
    return ts_node_child(child->parent, child->index - 1);
  else
    return NULL;
}

TSNode *ts_node_next_sibling(TSNode *child) {
  if (child->parent)
    return ts_node_child(child->parent, child->index + 1);
  else
    return NULL;
}

size_t ts_node_child_count(const TSNode *parent) {
  size_t result;
  ts_tree_visible_children(parent->content, &result);
  return result;
}

TSNode *ts_node_child(TSNode *parent, size_t i) {
  size_t count;
  TSTreeChild *children = ts_tree_visible_children(parent->content, &count);
  if (i >= count)
    return NULL;
  size_t pos = parent->position + children[i].offset;
  return ts_node_make(children[i].tree, parent, i, pos, parent->names);
}

TSNode *ts_node_find_for_range(TSNode *parent, size_t min, size_t max) {
  size_t count;
  TSTreeChild *children = ts_tree_visible_children(parent->content, &count);
  for (size_t i = 0; i < count; i++) {
    TSTreeChild child = children[i];
    size_t pos = parent->position + child.offset;
    if (pos > min)
      break;
    if (pos + child.tree->size > max) {
      TSNode *node = ts_node_make(child.tree, parent, i, pos, parent->names);
      TSNode *result = ts_node_find_for_range(node, min, max);
      ts_node_release(node);
      return result;
    }
  }

  ts_node_retain(parent);
  return parent;
}

TSNode *ts_node_find_for_pos(TSNode *parent, size_t position) {
  return ts_node_find_for_range(parent, position, position);
}
