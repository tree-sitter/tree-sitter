#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/length.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const TSTree *tree, TSLength position) {
  return (TSNode){.data = tree, .position = position };
}

static inline const TSTree *get_tree(TSNode this) {
  return this.data;
}

TSLength ts_node_pos(TSNode this) {
  return ts_length_add(this.position, get_tree(this)->padding);
}

TSLength ts_node_size(TSNode this) {
  return get_tree(this)->size;
}

bool ts_node_eq(TSNode this, TSNode other) {
  return ts_tree_eq(get_tree(this), get_tree(other)) &&
         ts_length_eq(this.position, other.position);
}

const char *ts_node_name(TSNode this, const TSDocument *document) {
  return document->parser.language->symbol_names[get_tree(this)->symbol];
}

const char *ts_node_string(TSNode this, const TSDocument *document) {
  return ts_tree_string(get_tree(this), document->parser.language->symbol_names);
}

typedef struct {
  TSNode node;
  size_t index;
} NodeWithIndex;

static inline NodeWithIndex ts_node_parent_with_index(TSNode this) {
  TSLength position = this.position;
  const TSTree *tree = get_tree(this);

  size_t index = 0;
  do {
    TSTree *parent = tree->parent;
    if (!parent)
      return (NodeWithIndex){ ts_node_null(), 0 };

    for (size_t i = 0; i < parent->child_count; i++) {
      TSTree *child = parent->children[i];
      if (child == tree)
        break;
      index += ts_tree_is_visible(child) ? 1 : child->visible_child_count;
      position = ts_length_sub(position, ts_tree_total_size(child));
    }

    tree = parent;
  } while (!ts_tree_is_visible(tree));

  return (NodeWithIndex){ ts_node_make(tree, position), index };
}

TSNode ts_node_parent(TSNode this) {
  return ts_node_parent_with_index(this).node;
}

TSNode ts_node_prev_sibling(TSNode this) {
  NodeWithIndex parent = ts_node_parent_with_index(this);
  if (parent.node.data && parent.index > 0)
    return ts_node_child(parent.node, parent.index - 1);
  else
    return ts_node_null();
}

TSNode ts_node_next_sibling(TSNode this) {
  NodeWithIndex parent = ts_node_parent_with_index(this);
  if (parent.node.data)
    return ts_node_child(parent.node, parent.index + 1);
  else
    return ts_node_null();
}

size_t ts_node_child_count(TSNode this) {
  return get_tree(this)->visible_child_count;
}

TSNode ts_node_child(TSNode this, size_t child_index) {
  TSLength position = this.position;
  const TSTree *tree = get_tree(this);

  size_t index = 0;
  for (size_t i = 0; i < tree->child_count; i++) {
    TSTree *child = tree->children[i];
    if (ts_tree_is_visible(child)) {
      if (index == child_index)
        return ts_node_make(child, position);
      index++;
    } else {
      size_t index_within = child_index - index;
      if (index_within < child->visible_child_count)
        return ts_node_child(ts_node_make(child, position), index_within);
      index += child->visible_child_count;
    }
    position = ts_length_add(position, ts_tree_total_size(child));
  }

  return ts_node_null();
}

TSNode ts_node_find_for_range(TSNode this, size_t min, size_t max) {
  TSNode node = this;
  bool did_descend = true;
  while (did_descend) {
    did_descend = false;
    const TSTree *tree = get_tree(node);
    TSLength position = node.position;
    for (size_t i = 0; i < tree->child_count; i++) {
      const TSTree *child = tree->children[i];
      if (position.chars + child->padding.chars > min)
        break;
      if (position.chars + child->padding.chars + child->size.chars > max) {
        node = ts_node_make(child, position);
        did_descend = true;
      }
      position = ts_length_add(position, ts_tree_total_size(child));
    }
  }
  return node;
}

TSNode ts_node_find_for_pos(TSNode this, size_t position) {
  return ts_node_find_for_range(this, position, position);
}
