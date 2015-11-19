#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"

TSTree *ts_tree_make_leaf(TSSymbol sym, TSLength padding, TSLength size,
													TSPoint padding_point,
													TSPoint size_point,
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
		.padding_point = padding_point,
		.size_point = size_point,
    .options = {.type = node_type },
  };

  if (sym == ts_builtin_sym_error) {
    result->options.fragile_left = true;
    result->options.fragile_right = true;
  }

  return result;
}

TSTree *ts_tree_make_error(TSLength size, TSLength padding,
													 TSPoint start_point,
													 TSPoint end_point,
													 char lookahead_char) {
  TSTree *result =
    ts_tree_make_leaf(ts_builtin_sym_error, padding, size, start_point,
											end_point, TSNodeTypeNamed);
  result->lookahead_char = lookahead_char;
  return result;
}

static void ts_tree__set_children(TSTree *self, TSTree **children,
                                  size_t child_count) {
  self->children = children;
  self->child_count = child_count;
  self->visible_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);
    child->context.parent = self;
    child->context.index = i;
    child->context.offset = ts_tree_total_size(self);

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
    } else {
      self->size =
        ts_length_add(ts_length_add(self->size, child->padding), child->size);
    }

    switch (child->options.type) {
      case TSNodeTypeNamed:
        self->visible_child_count++;
        self->named_child_count++;
        break;
      case TSNodeTypeAnonymous:
        self->visible_child_count++;
        break;
      case TSNodeTypeHidden:
        self->visible_child_count += child->visible_child_count;
        self->named_child_count += child->named_child_count;
        break;
    }
  }

  if (child_count > 0) {
    if (children[0]->options.fragile_left)
      self->options.fragile_left = true;
    if (children[child_count - 1]->options.fragile_right)
      self->options.fragile_right = true;
  }
}

TSTree *ts_tree_make_node(TSSymbol symbol, size_t child_count,
                          TSTree **children, TSNodeType node_type) {
  TSTree *result =
    ts_tree_make_leaf(symbol, ts_length_zero(), ts_length_zero(), ts_point_zero(), ts_point_zero(), node_type);
  ts_tree__set_children(result, children, child_count);
  return result;
}

void ts_tree_retain(TSTree *self) {
  assert(self->ref_count > 0);
  self->ref_count++;
}

void ts_tree_release(TSTree *self) {
  assert(self->ref_count > 0);
  self->ref_count--;
  if (self->ref_count == 0) {
    for (size_t i = 0; i < self->child_count; i++)
      ts_tree_release(self->children[i]);
    if (self->child_count > 0)
      free(self->children);
    free(self);
  }
}

TSLength ts_tree_total_size(const TSTree *self) {
  return ts_length_add(self->padding, self->size);
}

TSPoint ts_tree_total_size_point(const TSTree *self) {
  return ts_point_add(self->padding_point, self->size_point);
}

bool ts_tree_eq(const TSTree *self, const TSTree *other) {
  if (self) {
    if (!other)
      return false;
  } else {
    return !other;
  }

  if (self->symbol != other->symbol)
    return false;
  if (self->symbol == ts_builtin_sym_error)
    return self->lookahead_char == other->lookahead_char;
  if (self->child_count != other->child_count)
    return false;
  if (self->visible_child_count != other->visible_child_count)
    return false;
  if (self->named_child_count != other->named_child_count)
    return false;
  for (size_t i = 0; i < self->child_count; i++)
    if (!ts_tree_eq(self->children[i], other->children[i]))
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

static size_t ts_tree__write_to_string(const TSTree *self,
                                       const char **symbol_names, char *string,
                                       size_t limit, int is_root,
                                       bool include_anonymous) {
  if (!self)
    return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  TSNodeType min_node_type =
    include_anonymous ? TSNodeTypeAnonymous : TSNodeTypeNamed;
  int visible = self->options.type >= min_node_type || is_root;

  if (visible && !is_root)
    cursor += snprintf(*writer, limit, " ");

  if (visible) {
    if (self->symbol == ts_builtin_sym_error && self->child_count == 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor += write_lookahead_to_string(*writer, limit, self->lookahead_char);
    } else {
      cursor += snprintf(*writer, limit, "(%s", symbol_names[self->symbol]);
    }
  }

  for (size_t i = 0; i < self->child_count; i++) {
    TSTree *child = self->children[i];
    cursor += ts_tree__write_to_string(child, symbol_names, *writer, limit, 0,
                                       include_anonymous);
  }

  if (visible)
    cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const TSTree *self, const char **symbol_names,
                     bool include_anonymous) {
  static char SCRATCH[1];
  size_t size = 1 + ts_tree__write_to_string(self, symbol_names, SCRATCH, 0, 1,
                                             include_anonymous);
  char *result = malloc(size * sizeof(char));
  ts_tree__write_to_string(self, symbol_names, result, size, 1,
                           include_anonymous);
  return result;
}

void ts_tree_prepend_children(TSTree *self, size_t count, TSTree **children) {
  if (count == 0)
    return;

  size_t new_child_count = count + self->child_count;
  TSTree **new_children = realloc(children, new_child_count * sizeof(TSTree *));
  memcpy(new_children + count, self->children,
         self->child_count * sizeof(TSTree *));
  free(self->children);

  ts_tree__set_children(self, new_children, new_child_count);
}

static inline long min(long a, long b) {
  return a <= b ? a : b;
}

void ts_tree_edit(TSTree *self, TSInputEdit edit) {
  size_t start = edit.position;
  size_t new_end = edit.position + edit.chars_inserted;
  size_t old_end = edit.position + edit.chars_removed;
  assert(old_end <= ts_tree_total_size(self).chars);

  self->options.has_changes = true;

  if (start < self->padding.chars) {
    self->padding.bytes = 0;
    long remaining_padding = self->padding.chars - old_end;
    if (remaining_padding >= 0) {
      self->padding.chars = new_end + remaining_padding;
    } else {
      self->padding.chars = new_end;
      self->size.chars += remaining_padding;
      self->size.bytes = 0;
    }
  } else if (start == self->padding.chars && edit.chars_removed == 0) {
    self->padding.bytes = 0;
    self->padding.chars += edit.chars_inserted;
  } else {
    self->size.bytes = 0;
    self->size.chars += (edit.chars_inserted - edit.chars_removed);
  }

  bool found_first_child = false;
  long remainder_to_delete = edit.chars_removed - edit.chars_inserted;
  size_t child_left = 0, child_right = 0;
  for (size_t i = 0; i < self->child_count; i++) {
    TSTree *child = self->children[i];
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
