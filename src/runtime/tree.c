#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"

TSTree *ts_tree_make_leaf(TSSymbol sym, TSLength size, TSLength padding,
                          bool is_hidden) {
  TSTree *result = malloc(sizeof(TSTree));
  *result = (TSTree){
    .ref_count = 1,
    .symbol = sym,
    .size = size,
    .child_count = 0,
    .children = NULL,
    .padding = padding,
    .options = is_hidden ? TSTreeOptionsHidden : 0,
  };
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
  TSTree *result = malloc(sizeof(TSTree));

  /*
   *  Determine the new node's size, padding and visible child count based on
   *  the given child nodes.
   */
  TSLength size = ts_length_zero(), padding = ts_length_zero();
  size_t visible_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);
    child->context.parent = result;
    child->context.index = i;

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
  if (symbol == ts_builtin_sym_error) {
    options |= (TSTreeOptionsFragileLeft | TSTreeOptionsFragileRight);
  } else {
    if (is_hidden)
      options |= TSTreeOptionsHidden;
    if (child_count == 1 && symbol != ts_builtin_sym_document &&
        (ts_tree_is_visible(children[0]) || ts_tree_is_wrapper(children[0])))
      options |= (TSTreeOptionsSingleton | TSTreeOptionsHidden);
    if (child_count > 0) {
      if (ts_tree_is_fragile_left(children[0]))
        options |= (TSTreeOptionsFragileLeft);
      if (ts_tree_is_fragile_right(children[child_count - 1]))
        options |= (TSTreeOptionsFragileRight);
    }
  }

  *result = (TSTree){.ref_count = 1,
                     .context = {.parent = NULL, .index = 0 },
                     .symbol = symbol,
                     .children = children,
                     .child_count = child_count,
                     .visible_child_count = visible_child_count,
                     .size = size,
                     .padding = padding,
                     .options = options };
  return result;
}

void ts_tree_retain(TSTree *tree) {
  assert(tree->ref_count > 0);
  tree->ref_count++;
}

void ts_tree_release(TSTree *tree) {
  assert(tree->ref_count > 0);
  tree->ref_count--;
  if (tree->ref_count == 0) {
    for (size_t i = 0; i < tree->child_count; i++)
      ts_tree_release(tree->children[i]);
    if (tree->child_count > 0)
      free(tree->children);
    free(tree);
  }
}

TSLength ts_tree_total_size(const TSTree *tree) {
  return ts_length_add(tree->padding, tree->size);
}

bool ts_tree_eq(const TSTree *node1, const TSTree *node2) {
  if (node1) {
    if (!node2)
      return false;
  } else {
    return !node2;
  }

  if (node1->symbol != node2->symbol)
    return false;
  if (node1->symbol == ts_builtin_sym_error)
    return node1->lookahead_char == node2->lookahead_char;
  if (node1->child_count != node2->child_count)
    return false;
  if (node1->visible_child_count != node2->visible_child_count)
    return false;
  for (size_t i = 0; i < node1->child_count; i++)
    if (!ts_tree_eq(node1->children[i], node2->children[i]))
      return false;
  return true;
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

static size_t ts_tree__write_to_string(const TSTree *tree,
                                       const char **symbol_names, char *string,
                                       size_t limit, int is_root) {
  if (!tree)
    return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  int visible = ts_tree_is_visible(tree) || is_root;

  if (visible && !is_root)
    cursor += snprintf(*writer, limit, " ");

  if (visible) {
    if (tree->symbol == ts_builtin_sym_error && tree->child_count == 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor += write_lookahead_to_string(*writer, limit, tree->lookahead_char);
    } else {
      cursor += snprintf(*writer, limit, "(%s", symbol_names[tree->symbol]);
    }
  }

  for (size_t i = 0; i < tree->child_count; i++) {
    TSTree *child = tree->children[i];
    cursor += ts_tree__write_to_string(child, symbol_names, *writer, limit, 0);
  }

  if (visible)
    cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const TSTree *tree, const char **symbol_names) {
  static char SCRATCH[1];
  size_t size = ts_tree__write_to_string(tree, symbol_names, SCRATCH, 0, 1) + 1;
  char *result = malloc(size * sizeof(char));
  ts_tree__write_to_string(tree, symbol_names, result, size, 1);
  return result;
}
