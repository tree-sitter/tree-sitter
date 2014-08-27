#include <string.h>
#include <stdio.h>
#include "tree_sitter/parser.h"
#include "runtime/tree.h"

static TSTree *ts_tree_make(TSSymbol symbol, size_t size, size_t offset,
                            int is_hidden) {
  TSTree *result = malloc(sizeof(TSTree));
  *result = (TSTree) { .ref_count = 1,
                       .symbol = symbol,
                       .size = size,
                       .offset = offset,
                       .options = is_hidden ? TSTreeOptionsHidden : 0, };
  return result;
}

TSTree *ts_tree_make_leaf(TSSymbol symbol, size_t size, size_t offset,
                          int is_hidden) {
  TSTree *result = ts_tree_make(symbol, size, offset, is_hidden);
  result->child_count = 0;
  result->children = NULL;
  return result;
}

TSTree *ts_tree_make_node(TSSymbol symbol, size_t child_count,
                          TSTree **children, int is_hidden) {
  size_t size = 0, offset = 0, visible_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);
    if (i == 0) {
      offset = child->offset;
      size = child->size;
    } else {
      size += child->offset + child->size;
    }

    if (ts_tree_is_visible(child))
      visible_child_count++;
    else
      visible_child_count += ts_tree_visible_child_count(child);
  }

  TSTreeOptions options = 0;
  if (is_hidden)
    options |= TSTreeOptionsHidden;
  if (child_count == 1 &&
      (ts_tree_is_visible(children[0]) || ts_tree_is_wrapper(children[0])))
    options |= (TSTreeOptionsWrapper | TSTreeOptionsHidden);

  TSTree *result = malloc(sizeof(TSTree) +
                          (visible_child_count * sizeof(TSChildWithPosition)));
  *result = (TSTree) { .ref_count = 1,
                       .symbol = symbol,
                       .size = size,
                       .offset = offset,
                       .options = options,
                       .children = children,
                       .child_count = child_count,
                       .visible_child_count = visible_child_count, };

  TSChildWithPosition *visible_children =
      ts_tree_visible_children(result, NULL);

  for (size_t i = 0, visible_i = 0, child_position = 0; i < child_count; i++) {
    TSTree *child = children[i];
    if (ts_tree_is_visible(child)) {
      visible_children[visible_i] =
          (TSChildWithPosition) { .tree = child, .position = child_position };
      visible_i++;
    } else {
      size_t granchild_count = 0;
      TSChildWithPosition *grandchildren =
          ts_tree_visible_children(child, &granchild_count);
      for (size_t j = 0; j < granchild_count; j++) {
        visible_children[visible_i] = (TSChildWithPosition) {
          .tree = grandchildren[j].tree,
          .position = grandchildren[j].position + child_position
        };
        visible_i++;
      }
    }

    child_position += child->offset + child->size;
  }

  return result;
}

TSTree *ts_tree_make_error(char lookahead_char, size_t expected_input_count,
                           const TSSymbol *expected_inputs, size_t size,
                           size_t offset) {
  TSTree *result = ts_tree_make(ts_builtin_sym_error, size, offset, 0);
  result->lookahead_char = lookahead_char;
  result->expected_input_count = expected_input_count;
  result->expected_inputs = expected_inputs;
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

size_t ts_tree_total_size(const TSTree *tree) {
  return tree->offset + tree->size;
}

int ts_tree_equals(const TSTree *node1, const TSTree *node2) {
  if (node1->symbol != node2->symbol)
    return 0;
  if (node1->symbol == ts_builtin_sym_error) {
    // check error equality
  } else {
    if (node1->child_count != node2->child_count)
      return 0;
    for (size_t i = 0; i < node1->child_count; i++)
      if (!ts_tree_equals(node1->children[i], node2->children[i]))
        return 0;
  }
  return 1;
}

TSTree **ts_tree_children(const TSTree *tree, size_t *count) {
  if (!tree || tree->symbol == ts_builtin_sym_error) {
    if (count)
      *count = 0;
    return NULL;
  }
  if (count)
    *count = tree->child_count;
  return tree->children;
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

static size_t tree_write_to_string(const TSTree *tree,
                                   const char **symbol_names, char *string,
                                   size_t limit, int is_root) {
  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  int visible = ts_tree_is_visible(tree);

  if (visible && !is_root)
    cursor += snprintf(*writer, limit, " ");

  if (!tree) {
    cursor += snprintf(*writer, limit, "(NULL)");
  } else if (tree->symbol == ts_builtin_sym_error) {
    cursor += snprintf(*writer, limit, "(ERROR ");
    cursor += write_lookahead_to_string(*writer, limit, tree->lookahead_char);
    cursor += snprintf(*writer, limit, ")");
  } else {
    if (visible || is_root)
      cursor += snprintf(*writer, limit, "(%s", symbol_names[tree->symbol]);
    for (size_t i = 0; i < tree->child_count; i++) {
      TSTree *child = tree->children[i];
      cursor += tree_write_to_string(child, symbol_names, *writer, limit, 0);
    }
    if (visible || is_root)
      cursor += snprintf(*writer, limit, ")");
  }

  return cursor - string;
}

char *ts_tree_string(const TSTree *tree, const char **symbol_names) {
  static char SCRATCH_STRING[1];
  size_t size =
      tree_write_to_string(tree, symbol_names, SCRATCH_STRING, 0, 1) + 1;
  char *result = malloc(size * sizeof(char));
  tree_write_to_string(tree, symbol_names, result, size, 1);
  return result;
}
