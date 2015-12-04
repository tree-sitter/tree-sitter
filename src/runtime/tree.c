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
                          TSSymbolMetadata metadata) {
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
    .options =
      {
        .visible = metadata.visible, .named = metadata.named,
      },
  };

  if (sym == ts_builtin_sym_error) {
    result->options.fragile_left = true;
    result->options.fragile_right = true;
  }

  return result;
}

TSTree *ts_tree_make_error(TSLength size, TSLength padding,
                           TSPoint size_point,
                           TSPoint padding_point,
                           char lookahead_char) {
  TSTree *result =
    ts_tree_make_leaf(ts_builtin_sym_error, padding, size, padding_point,
                      size_point, (TSSymbolMetadata){
                                       .visible = true, .named = true,
                                     });
  result->lookahead_char = lookahead_char;
  return result;
}

void ts_tree_assign_parents(TSTree *self) {
  TSLength offset = ts_length_zero();
  TSPoint offset_point = ts_point_zero();
  for (size_t i = 0; i < self->child_count; i++) {
    TSTree *child = self->children[i];
    if (child->context.parent != self) {
      child->context.parent = self;
      child->context.index = i;
      child->context.offset = offset;
      child->context.offset_point = offset_point;
      ts_tree_assign_parents(child);
    }
    offset = ts_length_add(offset, ts_tree_total_size(child));
    offset_point = ts_point_add(offset_point, ts_tree_total_size_point(child));
  }
}

void ts_tree_set_children(TSTree *self, size_t child_count, TSTree **children) {
  self->children = children;
  self->child_count = child_count;
  self->named_child_count = 0;
  self->visible_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];
    ts_tree_retain(child);

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
      self->padding_point = child->padding_point;
      self->size_point = child->size_point;
    } else {
      self->size =
        ts_length_add(ts_length_add(self->size, child->padding), child->size);
      self->size_point = ts_point_add(ts_point_add(self->size_point, child->padding_point), child->size_point);
    }

    if (child->options.visible) {
      self->visible_child_count++;
      if (child->options.named)
        self->named_child_count++;
    } else {
      self->visible_child_count += child->visible_child_count;
      self->named_child_count += child->named_child_count;
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
                          TSTree **children, TSSymbolMetadata metadata) {
  TSTree *result =
    ts_tree_make_leaf(symbol, ts_length_zero(), ts_length_zero(), ts_point_zero(), ts_point_zero(), metadata);
  ts_tree_set_children(result, child_count, children);
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

size_t ts_tree_offset_column(const TSTree *self) {
  size_t column = self->padding_point.column;

  if (self->padding_point.row > 0) {
    return column;
  }

  const TSTree *parent = self;
  TSPoint offset_point;
  do {
    offset_point = parent->context.offset_point;
    column += offset_point.column;

    parent = parent->context.parent;
    if (!parent) break;
  } while (offset_point.row == 0);

  return column;
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
  if (self->options.visible != other->options.visible)
    return false;
  if (self->options.named != other->options.named)
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

int ts_tree_compare(const TSTree *left, const TSTree *right) {
  if (left->symbol < right->symbol)
    return -1;
  if (right->symbol < left->symbol)
    return 1;
  if (left->child_count < right->child_count)
    return -1;
  if (right->child_count < left->child_count)
    return 1;
  for (size_t i = 0; i < left->child_count; i++) {
    TSTree *left_child = left->children[i];
    TSTree *right_child = right->children[i];
    switch (ts_tree_compare(left_child, right_child)) {
      case -1:
        return -1;
      case 1:
        return 1;
      default:
        break;
    }
  }
  return 0;
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
                                       size_t limit, bool is_root,
                                       bool include_anonymous) {
  if (!self)
    return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  bool visible = is_root || (self->options.visible &&
                             (include_anonymous || self->options.named));

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
    cursor += ts_tree__write_to_string(child, symbol_names, *writer, limit,
                                       false, include_anonymous);
  }

  if (visible)
    cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const TSTree *self, const char **symbol_names,
                     bool include_anonymous) {
  static char SCRATCH[1];
  size_t size = 1 + ts_tree__write_to_string(self, symbol_names, SCRATCH, 0,
                                             true, include_anonymous);
  char *result = malloc(size * sizeof(char));
  ts_tree__write_to_string(self, symbol_names, result, size, true,
                           include_anonymous);
  return result;
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
