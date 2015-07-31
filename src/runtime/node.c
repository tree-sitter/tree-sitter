#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/length.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const TSTree *tree, TSLength position) {
  return (TSNode){.data = tree, .position = position };
}

static inline const TSTree *get_tree(TSNode tree) {
  return tree.data;
}

TSLength ts_node_pos(TSNode tree) {
  return tree.position;
}

TSLength ts_node_size(TSNode tree) {
  return get_tree(tree)->size;
}

bool ts_node_eq(TSNode left, TSNode right) {
  return ts_tree_eq(get_tree(left), get_tree(right)) &&
         ts_length_eq(left.position, right.position);
}

const char *ts_node_name(TSNode tree, const TSDocument *document) {
  return document->parser.language->symbol_names[get_tree(tree)->symbol];
}

const char *ts_node_string(TSNode tree, const TSDocument *document) {
  return ts_tree_string(get_tree(tree), document->parser.language->symbol_names);
}

typedef struct {
  TSNode ref;
  size_t index;
} ParentWithIndex;

static inline ParentWithIndex ts_node_parent_with_index(TSNode ref) {
  const TSTree *tree = get_tree(ref);
  size_t index = 0;
  TSLength position = ts_length_sub(ref.position, tree->padding);

  do {
    TSTree *parent = tree->parent;
    if (!parent)
      return (ParentWithIndex){ ts_node_null(), 0 };

    for (size_t i = 0; i < parent->child_count; i++) {
      TSTree *child = parent->children[i];
      if (child == tree)
        break;
      if (ts_tree_is_visible(child)) {
        index += 1;
      } else {
        size_t child_count;
        ts_tree_visible_children(child, &child_count);
        index += child_count;
      }
      position = ts_length_sub(position, ts_tree_total_size(child));
    }
    tree = parent;
  } while (!ts_tree_is_visible(tree));

  return (ParentWithIndex){
    ts_node_make(tree, ts_length_add(position, tree->padding)), index
  };
}

TSNode ts_node_parent(TSNode ref) {
  return ts_node_parent_with_index(ref).ref;
}

TSNode ts_node_prev_sibling(TSNode ref) {
  ParentWithIndex parent = ts_node_parent_with_index(ref);
  if (parent.ref.data && parent.index > 0)
    return ts_node_child(parent.ref, parent.index - 1);
  else
    return ts_node_null();
}

TSNode ts_node_next_sibling(TSNode ref) {
  ParentWithIndex parent = ts_node_parent_with_index(ref);
  if (parent.ref.data)
    return ts_node_child(parent.ref, parent.index + 1);
  else
    return ts_node_null();
}

size_t ts_node_child_count(TSNode parent) {
  size_t result;
  ts_tree_visible_children(get_tree(parent), &result);
  return result;
}

TSNode ts_node_child(TSNode ref, size_t i) {
  size_t count;
  TSTreeChild *children = ts_tree_visible_children(get_tree(ref), &count);
  if (i >= count)
    return ts_node_null();
  TSLength position = ts_length_add(ref.position, children[i].offset);
  return ts_node_make(children[i].tree, position);
}

TSNode ts_node_find_for_range(TSNode ref, size_t min, size_t max) {
  bool did_descend = true;
  while (did_descend) {
    did_descend = false;
    size_t count;
    TSTreeChild *children = ts_tree_visible_children(get_tree(ref), &count);

    for (size_t i = 0; i < count; i++) {
      TSTreeChild child = children[i];
      TSLength position = ts_length_add(ref.position, child.offset);
      if (position.chars > min)
        break;
      if (position.chars + child.tree->size.chars > max) {
        ref = ts_node_make(child.tree, position);
        did_descend = true;
      }
    }
  }
  return ref;
}

TSNode ts_node_find_for_pos(TSNode ref, size_t position) {
  return ts_node_find_for_range(ref, position, position);
}
