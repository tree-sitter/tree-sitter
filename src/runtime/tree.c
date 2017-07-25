#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "runtime/alloc.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/language.h"
#include "runtime/error_costs.h"

TSStateId TS_TREE_STATE_NONE = USHRT_MAX;

void ts_external_token_state_init(TSExternalTokenState *self, const char *content, unsigned length) {
  self->length = length;
  if (length > sizeof(self->short_data)) {
    self->long_data = ts_malloc(length);
    memcpy(self->long_data, content, length);
  } else {
    memcpy(self->short_data, content, length);
  }
}

void ts_external_token_state_delete(TSExternalTokenState *self) {
  if (self->length > sizeof(self->short_data)) {
    ts_free(self->long_data);
  }
}

const char *ts_external_token_state_data(const TSExternalTokenState *self) {
  if (self->length > sizeof(self->short_data)) {
    return self->long_data;
  } else {
    return self->short_data;
  }
}

bool ts_external_token_state_eq(const TSExternalTokenState *a, const TSExternalTokenState *b) {
  return a == b ||
    (a->length == b->length &&
     memcmp(ts_external_token_state_data(a), ts_external_token_state_data(b), a->length) == 0);
}

Tree *ts_tree_make_leaf(TSSymbol symbol, Length padding, Length size, const TSLanguage *language) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  Tree *result = ts_malloc(sizeof(Tree));
  *result = (Tree){
    .ref_count = 1,
    .symbol = symbol,
    .size = size,
    .child_count = 0,
    .children = NULL,
    .visible_child_count = 0,
    .named_child_count = 0,
    .alias_sequence_id = 0,
    .padding = padding,
    .visible = metadata.visible,
    .named = metadata.named,
    .has_changes = false,
    .first_leaf = {
      .symbol = symbol,
      .lex_mode = {0, 0},
    },
    .has_external_tokens = false,
  };
  return result;
}

bool ts_tree_array_copy(TreeArray self, TreeArray *dest) {
  Tree **contents = NULL;
  if (self.capacity > 0) {
    contents = ts_calloc(self.capacity, sizeof(Tree *));
    memcpy(contents, self.contents, self.size * sizeof(Tree *));
    for (uint32_t i = 0; i < self.size; i++)
      ts_tree_retain(contents[i]);
  }

  dest->size = self.size;
  dest->capacity = self.capacity;
  dest->contents = contents;
  return true;
}

void ts_tree_array_delete(TreeArray *self) {
  for (uint32_t i = 0; i < self->size; i++) {
    ts_tree_release(self->contents[i]);
  }
  array_delete(self);
}

uint32_t ts_tree_array_essential_count(const TreeArray *self) {
  uint32_t result = 0;
  for (uint32_t i = 0; i < self->size; i++) {
    Tree *tree = self->contents[i];
    if (!tree->extra && tree->symbol != ts_builtin_sym_error)
      result++;
  }
  return result;
}

TreeArray ts_tree_array_remove_last_n(TreeArray *self, uint32_t remove_count) {
  TreeArray result = array_new();
  if (self->size == 0 || remove_count == 0) return result;

  uint32_t count = 0;
  uint32_t split_index = self->size - 1;
  for (; split_index + 1 > 0; split_index--) {
    Tree *tree = self->contents[split_index];
    if (!tree->extra) {
      count++;
      if (count == remove_count) break;
    }
  }

  array_grow(&result, self->size - split_index);
  for (uint32_t i = split_index; i < self->size; i++) {
    array_push(&result, self->contents[i]);
  }

  self->size = split_index;
  return result;
}

TreeArray ts_tree_array_remove_trailing_extras(TreeArray *self) {
  TreeArray result = array_new();

  uint32_t i = self->size - 1;
  for (; i + 1 > 0; i--) {
    Tree *child = self->contents[i];
    if (!child->extra) break;
    array_push(&result, child);
  }

  self->size = i + 1;
  ts_tree_array_reverse(&result);
  return result;
}

void ts_tree_array_reverse(TreeArray *self) {
  for (uint32_t i = 0, limit = self->size / 2; i < limit; i++) {
    size_t reverse_index = self->size - 1 - i;
    Tree *swap = self->contents[i];
    self->contents[i] = self->contents[reverse_index];
    self->contents[reverse_index] = swap;
  }
}

Tree *ts_tree_make_error(Length size, Length padding, int32_t lookahead_char,
                         const TSLanguage *language) {
  Tree *result = ts_tree_make_leaf(ts_builtin_sym_error, padding, size, language);
  result->fragile_left = true;
  result->fragile_right = true;
  result->lookahead_char = lookahead_char;
  return result;
}

Tree *ts_tree_make_copy(Tree *self) {
  Tree *result = ts_malloc(sizeof(Tree));
  *result = *self;
  result->ref_count = 1;
  return result;
}

void ts_tree_assign_parents(Tree *self, TreePath *path, const TSLanguage *language) {
  array_clear(path);
  array_push(path, ((TreePathEntry){self, length_zero(), 0, 0}));
  while (path->size > 0) {
    Tree *tree = array_pop(path).tree;
    Length offset = length_zero();
    const TSSymbol *alias_sequence = ts_language_alias_sequence(language, tree->alias_sequence_id);
    uint32_t non_extra_index = 0;
    for (uint32_t i = 0; i < tree->child_count; i++) {
      Tree *child = tree->children[i];
      if (child->context.parent != tree || child->context.index != i) {
        child->context.parent = tree;
        child->context.index = i;
        child->context.offset = offset;
        if (!child->extra && alias_sequence && alias_sequence[non_extra_index] != 0) {
          TSSymbolMetadata metadata = ts_language_symbol_metadata(language, alias_sequence[non_extra_index]);
          child->context.alias_symbol = alias_sequence[non_extra_index];
          child->context.alias_is_named = metadata.named;
        } else {
          child->context.alias_symbol = 0;
          child->context.alias_is_named = false;
        }
        array_push(path, ((TreePathEntry){child, length_zero(), 0, 0}));
      }
      offset = length_add(offset, ts_tree_total_size(child));
      if (!child->extra) non_extra_index++;
    }
  }
}


void ts_tree_set_children(Tree *self, uint32_t child_count, Tree **children,
                          const TSLanguage *language) {
  if (self->child_count > 0) ts_free(self->children);

  self->children = children;
  self->child_count = child_count;
  self->named_child_count = 0;
  self->visible_child_count = 0;
  self->error_cost = 0;
  self->has_external_tokens = false;
  self->dynamic_precedence = 0;

  uint32_t non_extra_index = 0;
  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self->alias_sequence_id);

  for (uint32_t i = 0; i < child_count; i++) {
    Tree *child = children[i];

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
      self->bytes_scanned = child->bytes_scanned;
    } else {
      uint32_t bytes_scanned = ts_tree_total_bytes(self) + child->bytes_scanned;
      if (bytes_scanned > self->bytes_scanned) self->bytes_scanned = bytes_scanned;
      self->size = length_add(self->size, ts_tree_total_size(child));
    }

    self->error_cost += child->error_cost;
    self->dynamic_precedence += child->dynamic_precedence;

    if (alias_sequence && alias_sequence[non_extra_index] != 0 && !child->extra) {
      self->visible_child_count++;
      if (ts_language_symbol_metadata(language, alias_sequence[non_extra_index]).named) {
        self->named_child_count++;
      }
    } else if (child->visible) {
      self->visible_child_count++;
      if (child->named) self->named_child_count++;
    } else if (child->child_count > 0) {
      self->visible_child_count += child->visible_child_count;
      self->named_child_count += child->named_child_count;
    }

    if (child->has_external_tokens) self->has_external_tokens = true;

    if (child->symbol == ts_builtin_sym_error) {
      self->fragile_left = self->fragile_right = true;
      self->parse_state = TS_TREE_STATE_NONE;
    }

    if (!child->extra) non_extra_index++;
  }

  if (self->symbol == ts_builtin_sym_error) {
    self->error_cost += ERROR_COST_PER_SKIPPED_CHAR * self->size.chars +
                        ERROR_COST_PER_SKIPPED_LINE * self->size.extent.row;
    for (uint32_t i = 0; i < child_count; i++)
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

Tree *ts_tree_make_node(TSSymbol symbol, uint32_t child_count, Tree **children,
                        unsigned alias_sequence_id, const TSLanguage *language) {
  Tree *result = ts_tree_make_leaf(symbol, length_zero(), length_zero(), language);
  result->alias_sequence_id = alias_sequence_id;
  ts_tree_set_children(result, child_count, children, language);
  return result;
}

Tree *ts_tree_make_error_node(TreeArray *children, const TSLanguage *language) {
  for (uint32_t i = 0; i < children->size; i++) {
    Tree *child = children->contents[i];
    if (child->symbol == ts_builtin_sym_error && child->child_count > 0) {
      array_splice(children, i, 1, child->child_count, child->children);
      i += child->child_count - 1;
      for (uint32_t j = 0; j < child->child_count; j++)
        ts_tree_retain(child->children[j]);
      ts_tree_release(child);
    }
  }

  Tree *result =
    ts_tree_make_node(ts_builtin_sym_error, children->size, children->contents, 0, language);

  result->fragile_left = true;
  result->fragile_right = true;
  return result;
}

void ts_tree_retain(Tree *self) {
  assert(self->ref_count > 0);
  self->ref_count++;
  assert(self->ref_count != 0);
}

void ts_tree_release(Tree *self) {
recur:
  assert(self->ref_count > 0);
  self->ref_count--;

  if (self->ref_count == 0) {
    if (self->child_count > 0) {
      for (uint32_t i = 0; i < self->child_count - 1; i++) {
        ts_tree_release(self->children[i]);
      }
      Tree *last_child = self->children[self->child_count - 1];
      ts_free(self->children);
      ts_free(self);
      self = last_child;
      goto recur;
    } else if (self->has_external_tokens) {
      ts_external_token_state_delete(&self->external_token_state);
    }

    ts_free(self);
  }
}

uint32_t ts_tree_start_column(const Tree *self) {
  uint32_t column = self->padding.extent.column;
  if (self->padding.extent.row > 0)
    return column;
  for (const Tree *tree = self; tree != NULL; tree = tree->context.parent) {
    column += tree->context.offset.extent.column;
    if (tree->context.offset.extent.row > 0)
      break;
  }
  return column;
}

uint32_t ts_tree_end_column(const Tree *self) {
  uint32_t result = self->size.extent.column;
  if (self->size.extent.row == 0)
    result += ts_tree_start_column(self);
  return result;
}

bool ts_tree_eq(const Tree *self, const Tree *other) {
  if (self) {
    if (!other) return false;
  } else {
    return !other;
  }

  if (self->symbol != other->symbol) return false;
  if (self->visible != other->visible) return false;
  if (self->named != other->named) return false;
  if (self->padding.bytes != other->padding.bytes) return false;
  if (self->size.bytes != other->size.bytes) return false;
  if (self->symbol == ts_builtin_sym_error) return self->lookahead_char == other->lookahead_char;
  if (self->child_count != other->child_count) return false;
  if (self->visible_child_count != other->visible_child_count) return false;
  if (self->named_child_count != other->named_child_count) return false;

  for (uint32_t i = 0; i < self->child_count; i++) {
    if (!ts_tree_eq(self->children[i], other->children[i])) {
      return false;
    }
  }
  return true;
}

int ts_tree_compare(const Tree *left, const Tree *right) {
  if (left->symbol < right->symbol)
    return -1;
  if (right->symbol < left->symbol)
    return 1;
  if (left->child_count < right->child_count)
    return -1;
  if (right->child_count < left->child_count)
    return 1;
  for (uint32_t i = 0; i < left->child_count; i++) {
    Tree *left_child = left->children[i];
    Tree *right_child = right->children[i];
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

bool ts_tree_invalidate_lookahead(Tree *self, uint32_t edit_byte_offset) {
  if (edit_byte_offset >= self->bytes_scanned) return false;
  self->has_changes = true;
  if (self->child_count > 0) {
    uint32_t child_start_byte = 0;
    for (uint32_t i = 0; i < self->child_count; i++) {
      Tree *child = self->children[i];
      if (child_start_byte > edit_byte_offset) break;
      ts_tree_invalidate_lookahead(child, edit_byte_offset - child_start_byte);
      child_start_byte += ts_tree_total_bytes(child);
    }
  }
  return true;
}


void ts_tree_edit(Tree *self, const TSInputEdit *edit) {
  uint32_t old_end_byte = edit->start_byte + edit->bytes_removed;
  uint32_t new_end_byte = edit->start_byte + edit->bytes_added;
  TSPoint old_end_point = point_add(edit->start_point, edit->extent_removed);
  TSPoint new_end_point = point_add(edit->start_point, edit->extent_added);

  assert(old_end_byte <= ts_tree_total_bytes(self));

  self->has_changes = true;

  if (edit->start_byte < self->padding.bytes) {
    length_set_unknown_chars(&self->padding);
    if (self->padding.bytes >= old_end_byte) {
      uint32_t trailing_padding_bytes = self->padding.bytes - old_end_byte;
      TSPoint trailing_padding_extent = point_sub(self->padding.extent, old_end_point);
      self->padding.bytes = new_end_byte + trailing_padding_bytes;
      self->padding.extent = point_add(new_end_point, trailing_padding_extent);
    } else {
      length_set_unknown_chars(&self->size);
      uint32_t removed_content_bytes = old_end_byte - self->padding.bytes;
      TSPoint removed_content_extent = point_sub(old_end_point, self->padding.extent);
      self->size.bytes = self->size.bytes - removed_content_bytes;
      self->size.extent = point_sub(self->size.extent, removed_content_extent);
      self->padding.bytes = new_end_byte;
      self->padding.extent = new_end_point;
    }
  } else if (edit->start_byte == self->padding.bytes && edit->bytes_removed == 0) {
    length_set_unknown_chars(&self->padding);
    self->padding.bytes = self->padding.bytes + edit->bytes_added;
    self->padding.extent = point_add(self->padding.extent, edit->extent_added);
  } else {
    length_set_unknown_chars(&self->size);
    uint32_t trailing_content_bytes = ts_tree_total_bytes(self) - old_end_byte;
    TSPoint trailing_content_extent = point_sub(ts_tree_total_extent(self), old_end_point);
    self->size.bytes = new_end_byte + trailing_content_bytes - self->padding.bytes;
    self->size.extent = point_sub(point_add(new_end_point, trailing_content_extent), self->padding.extent);
  }

  bool found_first_child = false;
  long remaining_bytes_to_delete = 0;
  TSPoint remaining_extent_to_delete = {0, 0};
  Length child_left, child_right = length_zero();
  for (uint32_t i = 0; i < self->child_count; i++) {
    Tree *child = self->children[i];
    child_left = child_right;
    child_right = length_add(child_left, ts_tree_total_size(child));

    if (!found_first_child && child_right.bytes >= edit->start_byte) {
      found_first_child = true;
      TSInputEdit child_edit = {
        .start_byte = edit->start_byte - child_left.bytes,
        .bytes_added = edit->bytes_added,
        .bytes_removed = edit->bytes_removed,
        .start_point = point_sub(edit->start_point, child_left.extent),
        .extent_added = edit->extent_added,
        .extent_removed = edit->extent_removed,
      };

      if (old_end_byte > child_right.bytes) {
        child_edit.bytes_removed = child_right.bytes - edit->start_byte;
        child_edit.extent_removed = point_sub(child_right.extent, edit->start_point);
        remaining_bytes_to_delete = old_end_byte - child_right.bytes;
        remaining_extent_to_delete = point_sub(old_end_point, child_right.extent);
      }

      ts_tree_edit(child, &child_edit);
    } else if (remaining_bytes_to_delete > 0) {
      TSInputEdit child_edit = {
        .start_byte = 0,
        .bytes_added = 0,
        .bytes_removed = min(remaining_bytes_to_delete, ts_tree_total_bytes(child)),
        .start_point = {0, 0},
        .extent_added = {0, 0},
        .extent_removed = point_min(remaining_extent_to_delete, ts_tree_total_size(child).extent),
      };
      remaining_bytes_to_delete -= child_edit.bytes_removed;
      remaining_extent_to_delete = point_sub(remaining_extent_to_delete, child_edit.extent_removed);
      ts_tree_edit(child, &child_edit);
    } else {
      ts_tree_invalidate_lookahead(child, edit->start_byte - child_left.bytes);
    }

    child_right = length_add(child_left, ts_tree_total_size(child));
    child->context.offset = child_left;
  }
}

Tree *ts_tree_last_external_token(Tree *tree) {
  if (!tree->has_external_tokens) return NULL;
  while (tree->child_count > 0) {
    for (uint32_t i = tree->child_count - 1; i + 1 > 0; i--) {
      Tree *child = tree->children[i];
      if (child->has_external_tokens) {
        tree = child;
        break;
      }
    }
  }
  return tree;
}

static size_t ts_tree__write_char_to_string(char *s, size_t n, int32_t c) {
  if (c == 0)
    return snprintf(s, n, "EOF");
  if (c == -1)
    return snprintf(s, n, "INVALID");
  else if (c == '\n')
    return snprintf(s, n, "'\\n'");
  else if (c == '\t')
    return snprintf(s, n, "'\\t'");
  else if (c == '\r')
    return snprintf(s, n, "'\\r'");
  else if (0 < c && c < 128 && isprint(c))
    return snprintf(s, n, "'%c'", c);
  else
    return snprintf(s, n, "%d", c);
}

static size_t ts_tree__write_to_string(const Tree *self, const TSLanguage *language,
                                       char *string, size_t limit, bool is_root,
                                       bool include_all) {
  if (!self) return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  bool visible =
    include_all ||
    is_root ||
    (self->visible && self->named) ||
    self->context.alias_is_named;

  if (visible && !is_root) {
    cursor += snprintf(*writer, limit, " ");
  }

  if (visible) {
    if (self->symbol == ts_builtin_sym_error && self->child_count == 0 && self->size.chars > 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor += ts_tree__write_char_to_string(*writer, limit, self->lookahead_char);
    } else {
      TSSymbol symbol = self->context.alias_symbol ? self->context.alias_symbol : self->symbol;
      cursor += snprintf(*writer, limit, "(%s", ts_language_symbol_name(language, symbol));
    }
  }

  for (uint32_t i = 0; i < self->child_count; i++) {
    Tree *child = self->children[i];
    cursor += ts_tree__write_to_string(child, language, *writer, limit, false, include_all);
  }

  if (visible) cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const Tree *self, const TSLanguage *language,
                     bool include_all) {
  static char SCRATCH[1];
  size_t size =
    ts_tree__write_to_string(self, language, SCRATCH, 0, true, include_all) + 1;
  char *result = ts_malloc(size * sizeof(char));
  ts_tree__write_to_string(self, language, result, size, true, include_all);
  return result;
}

void ts_tree__print_dot_graph(const Tree *self, uint32_t byte_offset,
                              const TSLanguage *language, FILE *f) {
  TSSymbol symbol = self->context.alias_symbol ? self->context.alias_symbol : self->symbol;
  fprintf(f, "tree_%p [label=\"%s\"", self, ts_language_symbol_name(language, symbol));

  if (self->child_count == 0)
    fprintf(f, ", shape=plaintext");
  if (self->extra)
    fprintf(f, ", fontcolor=gray");

  fprintf(f, ", tooltip=\"range:%u - %u\nstate:%d\nerror-cost:%u\"]\n",
          byte_offset, byte_offset + ts_tree_total_bytes(self), self->parse_state,
          self->error_cost);
  for (uint32_t i = 0; i < self->child_count; i++) {
    const Tree *child = self->children[i];
    ts_tree__print_dot_graph(child, byte_offset, language, f);
    fprintf(f, "tree_%p -> tree_%p [tooltip=%u]\n", self, child, i);
    byte_offset += ts_tree_total_bytes(child);
  }
}

void ts_tree_print_dot_graph(const Tree *self, const TSLanguage *language,
                             FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "edge [arrowhead=none]\n");
  ts_tree__print_dot_graph(self, 0, language, f);
  fprintf(f, "}\n");
}

TSExternalTokenState empty_state = {.length = 0, .short_data = {}};

bool ts_tree_external_token_state_eq(const Tree *self, const Tree *other) {
  const TSExternalTokenState *state1 = &empty_state;
  const TSExternalTokenState *state2 = &empty_state;
  if (self && self->has_external_tokens) state1 = &self->external_token_state;
  if (other && other->has_external_tokens) state2 = &other->external_token_state;
  return ts_external_token_state_eq(state1, state2);
}
