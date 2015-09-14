#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"

TSTree *ts_tree_make_leaf(TSSymbol sym, TSLength padding, TSLength size,
                          TSNodeType node_type) {
  TSTree *result = malloc(sizeof(TSTree));
  *result = (TSTree){
    .ref_count = 1,
    .symbol = sym,
    .size = size,
    .child_count = 0,
    .visible_child_count = 0,
    .named_child_count = 0,
    .children = NULL,
    .padding = padding,
    .options = {.type = node_type },
  };

  if (sym == ts_builtin_sym_error) {
    result->options.fragile_left = true;
    result->options.fragile_right = true;
  }

  return result;
}

TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char) {
  TSTree *result =
    ts_tree_make_leaf(ts_builtin_sym_error, padding, size, TSNodeTypeNamed);
  result->lookahead_char = lookahead_char;
  return result;
}

static void ts_tree__set_children(TSTree *this, TSTree **children,
                                  size_t child_count) {
  this->children = children;
  this->child_count = child_count;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);
    child->context.parent = this;
    child->context.index = i;
    child->context.offset = ts_tree_total_size(this);

    if (i == 0) {
      this->padding = child->padding;
      this->size = child->size;
    } else {
      this->size =
        ts_length_add(ts_length_add(this->size, child->padding), child->size);
    }

    switch (child->options.type) {
      case TSNodeTypeNamed:
        this->visible_child_count++;
        this->named_child_count++;
        break;
      case TSNodeTypeAnonymous:
        this->visible_child_count++;
        break;
      case TSNodeTypeHidden:
        this->visible_child_count += child->visible_child_count;
        this->named_child_count += child->named_child_count;
        break;
    }
  }

  if (child_count > 0) {
    if (children[0]->options.fragile_left)
      this->options.fragile_left = true;
    if (children[child_count - 1]->options.fragile_right)
      this->options.fragile_right = true;
  }
}

TSTree *ts_tree_make_node(TSSymbol symbol, size_t child_count,
                          TSTree **children, TSNodeType node_type) {
  TSTree *result =
    ts_tree_make_leaf(symbol, ts_length_zero(), ts_length_zero(), node_type);
  ts_tree__set_children(result, children, child_count);
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
  if (node1->named_child_count != node2->named_child_count)
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
  int visible = tree->options.type == TSNodeTypeNamed || is_root;

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

void ts_tree_prepend_children(TSTree *tree, size_t count, TSTree **children) {
  if (count == 0)
    return;

  size_t new_child_count = count + tree->child_count;
  TSTree **new_children = realloc(children, new_child_count * sizeof(TSTree *));
  memcpy(new_children + count, tree->children,
         tree->child_count * sizeof(TSTree *));
  free(tree->children);

  ts_tree__set_children(tree, new_children, new_child_count);
}

static inline long min(long a, long b) {
  return a <= b ? a : b;
}

void ts_tree_edit(TSTree *tree, TSInputEdit edit) {
  size_t start = edit.position;
  size_t old_end = edit.position + edit.chars_removed;
  size_t new_end = edit.position + edit.chars_inserted;

  assert(start >= 0);
  assert(old_end <= ts_tree_total_size(tree).chars);

  tree->options.has_changes = true;

  if (start < tree->padding.chars) {
    tree->padding.bytes = 0;
    long remaining_padding = tree->padding.chars - old_end;
    if (remaining_padding >= 0) {
      tree->padding.chars = new_end + remaining_padding;
    } else {
      tree->padding.chars = new_end;
      tree->size.chars += remaining_padding;
      tree->size.bytes = 0;
    }
  } else if (start == tree->padding.chars && edit.chars_removed == 0) {
    tree->padding.bytes = 0;
    tree->padding.chars += edit.chars_inserted;
  } else {
    tree->size.bytes = 0;
    tree->size.chars += (edit.chars_inserted - edit.chars_removed);
  }

  bool found_first_child = false;
  long remainder_to_delete = edit.chars_removed - edit.chars_inserted;
  size_t child_left = 0, child_right = 0;
  for (size_t i = 0; i < tree->child_count; i++) {
    TSTree *child = tree->children[i];
    size_t child_size = ts_tree_total_size(child).chars;
    child_left = child_right;
    child_right += child_size;

    if (!found_first_child) {
      if (child_right >= start) {
        found_first_child = true;
        size_t chars_removed = min(edit.chars_removed, child_right - start);
        remainder_to_delete -= (chars_removed - edit.chars_inserted);
        ts_tree_edit(child, (TSInputEdit){
                              .position = start - child_left,
                              .chars_inserted = edit.chars_inserted,
                              .chars_removed = chars_removed,
                            });
      }
    } else {
      if (remainder_to_delete > 0) {
        size_t chars_removed = min(remainder_to_delete, child_size);
        remainder_to_delete -= chars_removed;
        ts_tree_edit(
          child,
          (TSInputEdit){
            .position = 0, .chars_inserted = 0, .chars_removed = chars_removed,
          });
      } else {
        break;
      }
    }
  }
}
