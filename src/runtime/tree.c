#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/error_costs.h"

TSStateId TS_TREE_STATE_NONE = USHRT_MAX;

TSTree *ts_tree_make_leaf(TSSymbol sym, TSLength padding, TSLength size,
                          TSSymbolMetadata metadata) {
  TSTree *result = ts_malloc(sizeof(TSTree));
  if (!result)
    return NULL;

  *result = (TSTree){
    .ref_count = 1,
    .symbol = sym,
    .size = size,
    .child_count = 0,
    .visible_child_count = 0,
    .named_child_count = 0,
    .children = NULL,
    .padding = padding,
    .visible = metadata.visible,
    .named = metadata.named,
    .first_leaf.symbol = sym,
    .has_changes = false,
  };

  return result;
}

bool ts_tree_array_copy(TreeArray self, TreeArray *dest) {
  TSTree **contents = NULL;
  if (self.capacity > 0) {
    contents = ts_calloc(self.capacity, sizeof(TSTree *));
    if (!contents)
      return false;
    memcpy(contents, self.contents, self.size * sizeof(TSTree *));
    for (size_t i = 0; i < self.size; i++)
      ts_tree_retain(contents[i]);
  }

  dest->size = self.size;
  dest->capacity = self.capacity;
  dest->contents = contents;
  return true;
}

void ts_tree_array_delete(TreeArray *self) {
  for (size_t i = 0; i < self->size; i++)
    ts_tree_release(self->contents[i]);
  array_delete(self);
}

size_t ts_tree_array_essential_count(const TreeArray *self) {
  size_t result = 0;
  for (size_t i = 0; i < self->size; i++) {
    TSTree *tree = self->contents[i];
    if (!tree->extra && tree->symbol != ts_builtin_sym_error)
      result++;
  }
  return result;
}

TSTree *ts_tree_make_error(TSLength size, TSLength padding, char lookahead_char) {
  TSTree *result = ts_tree_make_leaf(ts_builtin_sym_error, padding, size,
                                     (TSSymbolMetadata){
                                       .visible = true, .named = true,
                                     });
  if (!result)
    return NULL;

  result->fragile_left = true;
  result->fragile_right = true;
  result->lookahead_char = lookahead_char;
  return result;
}

TSTree *ts_tree_make_copy(TSTree *self) {
  TSTree *result = ts_malloc(sizeof(TSTree));
  if (!result)
    return NULL;

  *result = *self;
  result->ref_count = 1;
  return result;
}

bool ts_tree_assign_parents(TSTree *self, TreePath *path) {
  array_clear(path);
  if (!array_push(path, ((TreePathEntry){self, ts_length_zero(), 0})))
    return false;
  while (path->size > 0) {
    TSTree *tree = array_pop(path).tree;
    TSLength offset = ts_length_zero();
    for (size_t i = 0; i < tree->child_count; i++) {
      TSTree *child = tree->children[i];
      if (child->context.parent != tree || child->context.index != i) {
        child->context.parent = tree;
        child->context.index = i;
        child->context.offset = offset;
        if (!array_push(path, ((TreePathEntry){child, ts_length_zero(), 0})))
          return false;
      }
      offset = ts_length_add(offset, ts_tree_total_size(child));
    }
  }
  return true;
}


void ts_tree_set_children(TSTree *self, size_t child_count, TSTree **children) {
  if (self->child_count > 0)
    ts_free(self->children);

  self->children = children;
  self->child_count = child_count;
  self->named_child_count = 0;
  self->visible_child_count = 0;
  self->error_cost = 0;

  for (size_t i = 0; i < child_count; i++) {
    TSTree *child = children[i];

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
    } else {
      self->size = ts_length_add(self->size, ts_tree_total_size(child));
    }

    self->error_cost += child->error_cost;

    if (child->visible) {
      self->visible_child_count++;
      if (child->named)
        self->named_child_count++;
    } else {
      self->visible_child_count += child->visible_child_count;
      self->named_child_count += child->named_child_count;
    }

    if (child->symbol == ts_builtin_sym_error) {
      self->fragile_left = self->fragile_right = true;
      self->parse_state = TS_TREE_STATE_NONE;
    }
  }

  if (self->symbol == ts_builtin_sym_error) {
    self->error_cost += ERROR_COST_PER_SKIPPED_CHAR * self->size.chars +
                        ERROR_COST_PER_SKIPPED_LINE * self->size.extent.row;
    for (size_t i = 0; i < child_count; i++)
      if (!self->children[i]->extra)
        self->error_cost += ERROR_COST_PER_SKIPPED_TREE;
  }

  if (child_count > 0) {
    self->first_leaf = children[0]->first_leaf;
    if (children[0]->fragile_left)
      self->fragile_left = true;
    if (children[child_count - 1]->fragile_right)
      self->fragile_right = true;
  }
}

TSTree *ts_tree_make_node(TSSymbol symbol, size_t child_count,
                          TSTree **children, TSSymbolMetadata metadata) {
  TSTree *result =
    ts_tree_make_leaf(symbol, ts_length_zero(), ts_length_zero(), metadata);
  if (!result)
    return NULL;

  ts_tree_set_children(result, child_count, children);
  return result;
}

TSTree *ts_tree_make_error_node(TreeArray *children) {
  for (size_t i = 0; i < children->size; i++) {
    TSTree *child = children->contents[i];
    if (child->symbol == ts_builtin_sym_error && child->child_count > 0) {
      if (!array_splice(children, i, 1, child->child_count, child->children))
        return NULL;
      i += child->child_count - 1;
      for (size_t j = 0; j < child->child_count; j++)
        ts_tree_retain(child->children[j]);
      ts_tree_release(child);
    }
  }

  TSTree *result = ts_tree_make_node(
    ts_builtin_sym_error, children->size, children->contents,
    (TSSymbolMetadata){.extra = false, .visible = true, .named = true });

  if (!result)
    return NULL;

  result->fragile_left = true;
  result->fragile_right = true;
  return result;
}

void ts_tree_retain(TSTree *self) {
  assert(self->ref_count > 0);
  self->ref_count++;
}

void ts_tree_release(TSTree *self) {
  if (!self)
    return;

recur:
  assert(self->ref_count > 0);
  self->ref_count--;

  if (self->ref_count == 0) {
    if (self->child_count > 0) {
      for (size_t i = 0; i < self->child_count - 1; i++)
        ts_tree_release(self->children[i]);
      TSTree *last_child = self->children[self->child_count - 1];
      ts_free(self->children);
      ts_free(self);

      self = last_child;
      goto recur;
    }

    ts_free(self);
  }
}

size_t ts_tree_start_column(const TSTree *self) {
  size_t column = self->padding.extent.column;
  if (self->padding.extent.row > 0)
    return column;
  for (const TSTree *tree = self; tree != NULL; tree = tree->context.parent) {
    column += tree->context.offset.extent.column;
    if (tree->context.offset.extent.row > 0)
      break;
  }
  return column;
}

size_t ts_tree_end_column(const TSTree *self) {
  size_t result = self->size.extent.column;
  if (self->size.extent.row == 0)
    result += ts_tree_start_column(self);
  return result;
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
  if (self->visible != other->visible)
    return false;
  if (self->named != other->named)
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

static inline long min(long a, long b) {
  return a <= b ? a : b;
}


void ts_tree_edit(TSTree *self, const TSInputEdit *edit) {
  size_t old_end_byte = edit->start_byte + edit->bytes_removed;
  size_t new_end_byte = edit->start_byte + edit->bytes_added;
  TSPoint old_end_point = ts_point_add(edit->start_point, edit->extent_removed);
  TSPoint new_end_point = ts_point_add(edit->start_point, edit->extent_added);

  assert(old_end_byte <= ts_tree_total_bytes(self));

  self->has_changes = true;

  if (edit->start_byte < self->padding.bytes) {
    ts_length_set_unknown(&self->padding);
    if (self->padding.bytes >= old_end_byte) {
      size_t trailing_padding_bytes = self->padding.bytes - old_end_byte;
      TSPoint trailing_padding_extent = ts_point_sub(self->padding.extent, old_end_point);
      self->padding.bytes = new_end_byte + trailing_padding_bytes;
      self->padding.extent = ts_point_add(new_end_point, trailing_padding_extent);
    } else {
      ts_length_set_unknown(&self->size);
      size_t removed_content_bytes = old_end_byte - self->padding.bytes;
      TSPoint removed_content_extent = ts_point_sub(old_end_point, self->padding.extent);
      self->size.bytes = self->size.bytes - removed_content_bytes;
      self->size.extent = ts_point_sub(self->size.extent, removed_content_extent);
      self->padding.bytes = new_end_byte;
      self->padding.extent = new_end_point;
    }
  } else if (edit->start_byte == self->padding.bytes && edit->bytes_removed == 0) {
    ts_length_set_unknown(&self->padding);
    self->padding.bytes = self->padding.bytes + edit->bytes_added;
    self->padding.extent = ts_point_add(self->padding.extent, edit->extent_added);
  } else {
    ts_length_set_unknown(&self->size);
    size_t trailing_content_bytes = ts_tree_total_bytes(self) - old_end_byte;
    TSPoint trailing_content_extent = ts_point_sub(ts_tree_total_extent(self), old_end_point);
    self->size.bytes = new_end_byte + trailing_content_bytes - self->padding.bytes;
    self->size.extent = ts_point_sub(ts_point_add(new_end_point, trailing_content_extent), self->padding.extent);
  }

  bool found_first_child = false;
  long remaining_bytes_to_delete = 0;
  TSPoint remaining_extent_to_delete = {0, 0};
  TSLength child_left, child_right = ts_length_zero();
  for (size_t i = 0; i < self->child_count; i++) {
    TSTree *child = self->children[i];
    child_left = child_right;

    if (!found_first_child) {
      child_right = ts_length_add(child_left, ts_tree_total_size(child));
      if (child_right.bytes >= edit->start_byte) {
        found_first_child = true;
        TSInputEdit child_edit = {
          .start_byte = edit->start_byte - child_left.bytes,
          .bytes_added = edit->bytes_added,
          .bytes_removed = edit->bytes_removed,
          .start_point = ts_point_sub(edit->start_point, child_left.extent),
          .extent_added = edit->extent_added,
          .extent_removed = edit->extent_removed,
        };

        if (old_end_byte > child_right.bytes) {
          child_edit.bytes_removed = child_right.bytes - edit->start_byte;
          child_edit.extent_removed = ts_point_sub(child_right.extent, edit->start_point);
          remaining_bytes_to_delete = old_end_byte - child_right.bytes;
          remaining_extent_to_delete = ts_point_sub(old_end_point, child_right.extent);
        }

        ts_tree_edit(child, &child_edit);
      }
    } else if (remaining_bytes_to_delete > 0) {
      TSInputEdit child_edit = {
        .start_byte = 0,
        .bytes_added = 0,
        .bytes_removed = min(remaining_bytes_to_delete, ts_tree_total_bytes(child)),
        .start_point = {0, 0},
        .extent_added = {0, 0},
        .extent_removed = ts_point_min(remaining_extent_to_delete, ts_tree_total_size(child).extent),
      };
      remaining_bytes_to_delete -= child_edit.bytes_removed;
      remaining_extent_to_delete = ts_point_sub(remaining_extent_to_delete, child_edit.extent_removed);
      ts_tree_edit(child, &child_edit);
    }

    child_right = ts_length_add(child_left, ts_tree_total_size(child));
    child->context.offset = child_left;
  }
}

static size_t ts_tree__write_char_to_string(char *s, size_t n, int32_t c) {
  if (c == 0)
    return snprintf(s, n, "EOF");
  else if (c == '\n')
    return snprintf(s, n, "'\\n'");
  else if (c == '\t')
    return snprintf(s, n, "'\\t'");
  else if (c == '\r')
    return snprintf(s, n, "'\\r'");
  else if (c < 128)
    return snprintf(s, n, "'%c'", c);
  else
    return snprintf(s, n, "%d", c);
}

static size_t ts_tree__write_to_string(const TSTree *self,
                                       const TSLanguage *language, char *string,
                                       size_t limit, bool is_root,
                                       bool include_all) {
  if (!self)
    return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  bool visible = include_all || is_root || (self->visible && self->named);

  if (visible && !is_root)
    cursor += snprintf(*writer, limit, " ");

  if (visible) {
    if (self->symbol == ts_builtin_sym_error && self->child_count == 0 &&
        self->size.chars > 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor +=
        ts_tree__write_char_to_string(*writer, limit, self->lookahead_char);
    } else {
      cursor += snprintf(*writer, limit, "(%s",
                         ts_language_symbol_name(language, self->symbol));
    }
  }

  for (size_t i = 0; i < self->child_count; i++) {
    TSTree *child = self->children[i];
    cursor += ts_tree__write_to_string(child, language, *writer, limit, false,
                                       include_all);
  }

  if (visible)
    cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const TSTree *self, const TSLanguage *language,
                     bool include_all) {
  static char SCRATCH[1];
  size_t size =
    ts_tree__write_to_string(self, language, SCRATCH, 0, true, include_all) + 1;
  char *result = ts_malloc(size * sizeof(char));
  ts_tree__write_to_string(self, language, result, size, true, include_all);
  return result;
}

void ts_tree__print_dot_graph(const TSTree *self, size_t byte_offset,
                              const TSLanguage *language, FILE *f) {
  fprintf(f, "tree_%p [label=\"%s\"", self,
          ts_language_symbol_name(language, self->symbol));

  if (self->child_count == 0)
    fprintf(f, ", shape=plaintext");
  if (self->extra)
    fprintf(f, ", fontcolor=gray");

  fprintf(f, ", tooltip=\"range:%lu - %lu\nstate:%d\nerror-cost:%u\"]\n",
          byte_offset, byte_offset + ts_tree_total_bytes(self), self->parse_state,
          self->error_cost);
  for (size_t i = 0; i < self->child_count; i++) {
    const TSTree *child = self->children[i];
    ts_tree__print_dot_graph(child, byte_offset, language, f);
    fprintf(f, "tree_%p -> tree_%p [tooltip=%lu]\n", self, child, i);
    byte_offset += ts_tree_total_bytes(child);
  }
}

void ts_tree_print_dot_graph(const TSTree *self, const TSLanguage *language,
                             FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "edge [arrowhead=none]\n");
  ts_tree__print_dot_graph(self, 0, language, f);
  fprintf(f, "}\n");
}
