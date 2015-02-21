#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"

TSTree *ts_tree_make_leaf(TSSymbol sym, TSLength size, TSLength padding,
                          bool is_hidden) {
  TSTree *result = malloc(sizeof(TSTree));
  *result = (TSTree) { .ref_count = 1,
                       .symbol = sym,
                       .size = size,
                       .child_count = 0,
                       .children = NULL,
                       .lookahead_char = 0,
                       .padding = padding,
                       .options = is_hidden ? TSTreeOptionsHidden : 0, };
  return result;
}

TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char) {
  TSTree *result = ts_tree_make_leaf(ts_builtin_sym_error, size, padding, false);
  ts_tree_set_fragile_left(result);
  ts_tree_set_fragile_right(result);
  result->lookahead_char = lookahead_char;
  return result;
}

TSTree *ts_tree_make_node(TSSymbol symbol, size_t child_count,
                          TSTree **children, bool is_hidden) {

  /*
   *  Determine the new node's size, padding and visible child count based on
   *  the given child nodes.
   */
  TSLength size = ts_length_zero(), padding = ts_length_zero();
  size_t visible_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);

    if (i == 0) {
      padding = child->padding;
      size = child->size;
    } else {
      size = ts_length_add(ts_length_add(size, child->padding), child->size);
    }

    if (ts_tree_is_visible(child))
      visible_child_count++;
    else
      visible_child_count += child->visible_child_count;
  }

  /*
   *  Mark the tree as hidden if it wraps a single child node.
   */
  TSTreeOptions options = 0;
  if (is_hidden)
    options |= TSTreeOptionsHidden;
  if (child_count == 1 &&
      (ts_tree_is_visible(children[0]) || ts_tree_is_wrapper(children[0])))
    options |= (TSTreeOptionsWrapper | TSTreeOptionsHidden);
  if (child_count > 0 && ts_tree_is_fragile_left(children[0]))
    options |= (TSTreeOptionsFragileLeft);
  if (child_count > 0 && ts_tree_is_fragile_right(children[child_count - 1]))
    options |= (TSTreeOptionsFragileRight);

  /*
   *  Store the visible child array adjacent to the tree itself. This avoids
   *  performing a second allocation and storing an additional pointer.
   */
  TSTree *result =
      malloc(sizeof(TSTree) + (visible_child_count * sizeof(TSTreeChild)));
  *result = (TSTree) { .ref_count = 1,
                       .symbol = symbol,
                       .children = children,
                       .child_count = child_count,
                       .visible_child_count = visible_child_count,
                       .size = size,
                       .padding = padding,
                       .options = options };

  /*
   *  Associate a relative offset with each of the visible child nodes, so that
   *  their positions can be queried without using the hidden child nodes.
   */
  TSTreeChild *visible_children = ts_tree_visible_children(result, NULL);
  TSLength offset = ts_length_zero();
  for (size_t i = 0, vis_i = 0; i < child_count; i++) {
    TSTree *child = children[i];

    if (i > 0)
      offset = ts_length_add(offset, child->padding);

    if (ts_tree_is_visible(child)) {
      visible_children[vis_i].tree = child;
      visible_children[vis_i].offset = offset;
      vis_i++;
    } else {
      size_t n = 0;
      TSTreeChild *grandchildren = ts_tree_visible_children(child, &n);
      for (size_t j = 0; j < n; j++) {
        visible_children[vis_i].tree = grandchildren[j].tree;
        visible_children[vis_i].offset =
            ts_length_add(offset, grandchildren[j].offset);
        vis_i++;
      }
    }

    offset = ts_length_add(offset, child->size);
  }

  return result;
}

void ts_tree_retain(TSTree *tree) { tree->ref_count++; }

void ts_tree_release(TSTree *tree) {
  tree->ref_count--;
  if (tree->ref_count == 0) {
    size_t count;
    TSTree **children = ts_tree_children(tree, &count);
    for (size_t i = 0; i < count; i++)
      ts_tree_release(children[i]);
    free(tree->children);
    free(tree);
  }
}

TSLength ts_tree_total_size(const TSTree *tree) {
  return ts_length_add(tree->padding, tree->size);
}

bool ts_tree_eq(const TSTree *node1, const TSTree *node2) {
  if (node1->symbol != node2->symbol)
    return false;
  if (node1->lookahead_char != node2->lookahead_char)
    return false;
  if (node1->child_count != node2->child_count)
    return false;
  if (node1->visible_child_count != node2->visible_child_count)
    return false;
  for (size_t i = 0; i < node1->child_count; i++)
    if (!ts_tree_eq(node1->children[i], node2->children[i]))
      return false;
  return true;
}

TSTree **ts_tree_children(const TSTree *tree, size_t *count) {
  if (count)
    *count = tree->child_count;
  return tree->children;
}

TSTreeChild *ts_tree_visible_children(const TSTree *tree, size_t *count) {
  if (count)
    *count = tree->visible_child_count;
  return (TSTreeChild *)(tree + 1);
}

static size_t write_lookahead_to_string(char *string, size_t limit,
                                        char lookahead) {
  switch (lookahead) {
    case '\0':
      return snprintf(string, limit, "<EOF>");
    default:
      return snprintf(string, limit, "'%c'", lookahead);
  }
}

static size_t tree_write_to_string(const TSTree *tree, const char **symbol_names,
                                   char *string, size_t limit, int is_root) {
  if (!tree)
    return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  int visible = ts_tree_is_visible(tree) || is_root;

  if (visible && !is_root)
    cursor += snprintf(*writer, limit, " ");

  if (visible) {
    if (tree->symbol == ts_builtin_sym_error) {
      cursor += snprintf(*writer, limit, "(ERROR ");
      cursor += write_lookahead_to_string(*writer, limit, tree->lookahead_char);
    } else {
      cursor += snprintf(*writer, limit, "(%s", symbol_names[tree->symbol]);
    }
  }

  for (size_t i = 0; i < tree->child_count; i++) {
    TSTree *child = tree->children[i];
    cursor += tree_write_to_string(child, symbol_names, *writer, limit, 0);
  }

  if (visible)
    cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const TSTree *tree, const char **symbol_names) {
  static char SCRATCH[1];
  size_t size = tree_write_to_string(tree, symbol_names, SCRATCH, 0, 1) + 1;
  char *result = malloc(size * sizeof(char));
  tree_write_to_string(tree, symbol_names, result, size, 1);
  return result;
}
