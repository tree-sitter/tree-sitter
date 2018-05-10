#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "runtime/alloc.h"
#include "runtime/atomic.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/language.h"
#include "runtime/error_costs.h"

TSStateId TS_TREE_STATE_NONE = USHRT_MAX;

// ExternalTokenState

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

// TreeArray

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

void ts_tree_array_delete(TreePool *pool, TreeArray *self) {
  for (uint32_t i = 0; i < self->size; i++) {
    ts_tree_release(pool, self->contents[i]);
  }
  array_delete(self);
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

// TreePool

static const uint32_t MAX_TREE_POOL_SIZE = 1024;

void ts_tree_pool_init(TreePool *self) {
  array_init(&self->free_trees);
  array_init(&self->tree_stack);
}

void ts_tree_pool_delete(TreePool *self) {
  if (self->free_trees.contents) {
    for (unsigned i = 0; i < self->free_trees.size; i++) {
      ts_free(self->free_trees.contents[i]);
    }
    array_delete(&self->free_trees);
  }
  if (self->tree_stack.contents) array_delete(&self->tree_stack);
}

Tree *ts_tree_pool_allocate(TreePool *self) {
  if (self->free_trees.size > 0) {
    return array_pop(&self->free_trees);
  } else {
    return ts_malloc(sizeof(Tree));
  }
}

void ts_tree_pool_free(TreePool *self, Tree *tree) {
  if (self->free_trees.size < MAX_TREE_POOL_SIZE) {
    array_push(&self->free_trees, tree);
  } else {
    ts_free(tree);
  }
}

// Tree

Tree *ts_tree_make_leaf(TreePool *pool, TSSymbol symbol, Length padding, Length size, const TSLanguage *language) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  Tree *result = ts_tree_pool_allocate(pool);
  *result = (Tree){
    .ref_count = 1,
    .symbol = symbol,
    .size = size,
    .visible_child_count = 0,
    .named_child_count = 0,
    .alias_sequence_id = 0,
    .padding = padding,
    .visible = metadata.visible,
    .named = metadata.named,
    .node_count = 1,
    .has_changes = false,
    .first_leaf = {
      .symbol = symbol,
      .lex_mode = {0, 0},
    },
    .has_external_tokens = false,
  };
  return result;
}

Tree *ts_tree_make_error(TreePool *pool, Length size, Length padding, int32_t lookahead_char,
                         const TSLanguage *language) {
  Tree *result = ts_tree_make_leaf(pool, ts_builtin_sym_error, padding, size, language);
  result->fragile_left = true;
  result->fragile_right = true;
  result->lookahead_char = lookahead_char;
  return result;
}

Tree *ts_tree_make_copy(TreePool *pool, Tree *self) {
  Tree *result = ts_tree_pool_allocate(pool);
  *result = *self;
  result->ref_count = 1;
  return result;
}

static void ts_tree__compress(Tree *self, unsigned count, const TSLanguage *language, TreeArray *stack) {
  unsigned initial_stack_size = stack->size;

  Tree *tree = self;
  for (unsigned i = 0; i < count; i++) {
    if (tree->ref_count > 1 || tree->children.size != 2) break;

    Tree *child = tree->children.contents[0];
    if (
      child->ref_count > 1 ||
      child->children.size != 2 ||
      child->symbol != tree->symbol
    ) break;

    Tree *grandchild = child->children.contents[0];
    if (
      grandchild->ref_count > 1 ||
      grandchild->children.size != 2 ||
      grandchild->symbol != tree->symbol
    ) break;

    tree->children.contents[0] = grandchild;
    child->children.contents[0] = grandchild->children.contents[1];
    grandchild->children.contents[1] = child;
    array_push(stack, tree);
    tree = grandchild;
  }

  while (stack->size > initial_stack_size) {
    tree = array_pop(stack);
    Tree *child = tree->children.contents[0];
    Tree *grandchild = child->children.contents[1];
    ts_tree_set_children(grandchild, &grandchild->children, language);
    ts_tree_set_children(child, &child->children, language);
    ts_tree_set_children(tree, &tree->children, language);
  }
}

void ts_tree_balance(Tree *self, TreePool *pool, const TSLanguage *language) {
  array_clear(&pool->tree_stack);
  array_push(&pool->tree_stack, self);
  while (pool->tree_stack.size > 0) {
    Tree *tree = array_pop(&pool->tree_stack);
    assert(tree);

    if (tree->repeat_depth > 0) {
      if (tree->children.contents[0]->repeat_depth > tree->children.contents[1]->repeat_depth) {
        unsigned n = (
          tree->children.contents[0]->repeat_depth -
          tree->children.contents[1]->repeat_depth
        );
        for (unsigned i = n / 2; i > 0; i /= 2) {
          ts_tree__compress(tree, i, language, &pool->tree_stack);
          n -= i;
        }
      }
    }

    for (uint32_t i = 0; i < tree->children.size; i++) {
      Tree *child = tree->children.contents[i];
      if (child->ref_count == 1) {
        array_push(&pool->tree_stack, child);
      }
    }
  }
}

void ts_tree_set_children(Tree *self, TreeArray *children, const TSLanguage *language) {
  if (self->children.size > 0 && children->contents != self->children.contents) {
    array_delete(&self->children);
  }

  self->children = *children;
  self->named_child_count = 0;
  self->visible_child_count = 0;
  self->error_cost = 0;
  self->repeat_depth = 0;
  self->node_count = 1;
  self->has_external_tokens = false;
  self->dynamic_precedence = 0;

  uint32_t non_extra_index = 0;
  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self->alias_sequence_id);

  for (uint32_t i = 0; i < self->children.size; i++) {
    Tree *child = self->children.contents[i];

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
      self->bytes_scanned = child->bytes_scanned;
    } else {
      uint32_t bytes_scanned = ts_tree_total_bytes(self) + child->bytes_scanned;
      if (bytes_scanned > self->bytes_scanned) self->bytes_scanned = bytes_scanned;
      self->size = length_add(self->size, ts_tree_total_size(child));
    }

    if (child->symbol != ts_builtin_sym_error_repeat) {
      self->error_cost += child->error_cost;
    }
    self->dynamic_precedence += child->dynamic_precedence;
    self->node_count += child->node_count;

    if (alias_sequence && alias_sequence[non_extra_index] != 0 && !child->extra) {
      self->visible_child_count++;
      if (ts_language_symbol_metadata(language, alias_sequence[non_extra_index]).named) {
        self->named_child_count++;
      }
    } else if (child->visible) {
      self->visible_child_count++;
      if (child->named) self->named_child_count++;
    } else if (child->children.size > 0) {
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

  if (self->symbol == ts_builtin_sym_error || self->symbol == ts_builtin_sym_error_repeat) {
    self->error_cost += ERROR_COST_PER_RECOVERY +
                        ERROR_COST_PER_SKIPPED_CHAR * self->size.bytes +
                        ERROR_COST_PER_SKIPPED_LINE * self->size.extent.row;
    for (uint32_t i = 0; i < self->children.size; i++) {
      Tree *child = self->children.contents[i];
      if (child->extra) continue;
      if (child->symbol == ts_builtin_sym_error && child->children.size == 0) continue;
      if (child->visible) {
        self->error_cost += ERROR_COST_PER_SKIPPED_TREE;
      } else {
        self->error_cost += ERROR_COST_PER_SKIPPED_TREE * child->visible_child_count;
      }
    }
  }

  if (self->children.size > 0) {
    Tree *first_child = self->children.contents[0];
    Tree *last_child = self->children.contents[self->children.size - 1];
    self->first_leaf = first_child->first_leaf;
    if (first_child->fragile_left) self->fragile_left = true;
    if (last_child->fragile_right) self->fragile_right = true;
    if (
      self->children.size == 2 &&
      !self->visible && !self->named &&
      first_child->symbol == self->symbol &&
      last_child->symbol == self->symbol
    ) {
      if (first_child->repeat_depth > last_child->repeat_depth) {
        self->repeat_depth = first_child->repeat_depth + 1;
      } else {
        self->repeat_depth = last_child->repeat_depth + 1;
      }
    }
  }
}

Tree *ts_tree_make_node(TreePool *pool, TSSymbol symbol, TreeArray *children,
                        unsigned alias_sequence_id, const TSLanguage *language) {
  Tree *result = ts_tree_make_leaf(pool, symbol, length_zero(), length_zero(), language);
  result->alias_sequence_id = alias_sequence_id;
  if (symbol == ts_builtin_sym_error || symbol == ts_builtin_sym_error_repeat) {
    result->fragile_left = true;
    result->fragile_right = true;
  }
  ts_tree_set_children(result, children, language);
  return result;
}

Tree *ts_tree_make_error_node(TreePool *pool, TreeArray *children, const TSLanguage *language) {
  return ts_tree_make_node(pool, ts_builtin_sym_error, children, 0, language);
}

Tree *ts_tree_make_missing_leaf(TreePool *pool, TSSymbol symbol, const TSLanguage *language) {
  Tree *result = ts_tree_make_leaf(pool, symbol, length_zero(), length_zero(), language);
  result->is_missing = true;
  result->error_cost = ERROR_COST_PER_MISSING_TREE + ERROR_COST_PER_RECOVERY;
  return result;
}

void ts_tree_retain(Tree *self) {
  assert(self->ref_count > 0);
  atomic_inc(&self->ref_count);
  assert(self->ref_count != 0);
}

void ts_tree_release(TreePool *pool, Tree *self) {
  array_clear(&pool->tree_stack);
  array_push(&pool->tree_stack, self);
  while (pool->tree_stack.size > 0) {
    Tree *tree = array_pop(&pool->tree_stack);
    assert(tree->ref_count > 0);
    if (atomic_dec(&tree->ref_count) == 0) {
      if (tree->children.size > 0) {
        for (uint32_t i = 0; i < tree->children.size; i++) {
          array_push(&pool->tree_stack, tree->children.contents[i]);
        }
        array_delete(&tree->children);
      } else if (tree->has_external_tokens) {
        ts_external_token_state_delete(&tree->external_token_state);
      }
      ts_tree_pool_free(pool, tree);
    }
  }
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
  if (self->children.size != other->children.size) return false;
  if (self->visible_child_count != other->visible_child_count) return false;
  if (self->named_child_count != other->named_child_count) return false;

  for (uint32_t i = 0; i < self->children.size; i++) {
    if (!ts_tree_eq(self->children.contents[i], other->children.contents[i])) {
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
  if (left->children.size < right->children.size)
    return -1;
  if (right->children.size < left->children.size)
    return 1;
  for (uint32_t i = 0; i < left->children.size; i++) {
    Tree *left_child = left->children.contents[i];
    Tree *right_child = right->children.contents[i];
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

static inline long min_byte(long a, long b) {
  return a <= b ? a : b;
}

bool ts_tree_invalidate_lookahead(Tree *self, uint32_t edit_byte_offset) {
  if (edit_byte_offset >= self->bytes_scanned) return false;
  self->has_changes = true;
  if (self->children.size > 0) {
    uint32_t child_start_byte = 0;
    for (uint32_t i = 0; i < self->children.size; i++) {
      Tree *child = self->children.contents[i];
      if (child_start_byte > edit_byte_offset) break;
      ts_tree_invalidate_lookahead(child, edit_byte_offset - child_start_byte);
      child_start_byte += ts_tree_total_bytes(child);
    }
  }
  return true;
}

static inline TSPoint ts_tree_total_extent(const Tree *self) {
  return point_add(self->padding.extent, self->size.extent);
}

void ts_tree_edit(Tree *self, const TSInputEdit *edit) {
  uint32_t old_end_byte = edit->start_byte + edit->bytes_removed;
  uint32_t new_end_byte = edit->start_byte + edit->bytes_added;
  TSPoint old_end_point = point_add(edit->start_point, edit->extent_removed);
  TSPoint new_end_point = point_add(edit->start_point, edit->extent_added);

  assert(old_end_byte <= ts_tree_total_bytes(self));

  self->has_changes = true;

  if (edit->start_byte < self->padding.bytes) {
    if (self->padding.bytes >= old_end_byte) {
      uint32_t trailing_padding_bytes = self->padding.bytes - old_end_byte;
      TSPoint trailing_padding_extent = point_sub(self->padding.extent, old_end_point);
      self->padding.bytes = new_end_byte + trailing_padding_bytes;
      self->padding.extent = point_add(new_end_point, trailing_padding_extent);
    } else {
      uint32_t removed_content_bytes = old_end_byte - self->padding.bytes;
      TSPoint removed_content_extent = point_sub(old_end_point, self->padding.extent);
      self->size.bytes = self->size.bytes - removed_content_bytes;
      self->size.extent = point_sub(self->size.extent, removed_content_extent);
      self->padding.bytes = new_end_byte;
      self->padding.extent = new_end_point;
    }
  } else if (edit->start_byte == self->padding.bytes && edit->bytes_removed == 0) {
    self->padding.bytes = self->padding.bytes + edit->bytes_added;
    self->padding.extent = point_add(self->padding.extent, edit->extent_added);
  } else {
    uint32_t trailing_content_bytes = ts_tree_total_bytes(self) - old_end_byte;
    TSPoint trailing_content_extent = point_sub(ts_tree_total_extent(self), old_end_point);
    self->size.bytes = new_end_byte + trailing_content_bytes - self->padding.bytes;
    self->size.extent = point_sub(point_add(new_end_point, trailing_content_extent), self->padding.extent);
  }

  bool found_first_child = false;
  long remaining_bytes_to_delete = 0;
  TSPoint remaining_extent_to_delete = {0, 0};
  Length child_left, child_right = length_zero();
  for (uint32_t i = 0; i < self->children.size; i++) {
    Tree *child = self->children.contents[i];
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
        .bytes_removed = min_byte(remaining_bytes_to_delete, ts_tree_total_bytes(child)),
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
  }
}

Tree *ts_tree_last_external_token(Tree *tree) {
  if (!tree->has_external_tokens) return NULL;
  while (tree->children.size > 0) {
    for (uint32_t i = tree->children.size - 1; i + 1 > 0; i--) {
      Tree *child = tree->children.contents[i];
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

static size_t ts_tree__write_to_string(const Tree *self, char *string, size_t limit,
                                       const TSLanguage *language, bool is_root,
                                       bool include_all, TSSymbol alias_symbol,
                                       bool alias_is_named) {
  if (!self) return snprintf(string, limit, "(NULL)");

  char *cursor = string;
  char **writer = (limit > 0) ? &cursor : &string;
  bool visible =
    include_all ||
    is_root ||
    self->is_missing ||
    (self->visible && self->named) ||
    alias_is_named;

  if (visible && !is_root) {
    cursor += snprintf(*writer, limit, " ");
  }

  if (visible) {
    if (self->symbol == ts_builtin_sym_error && self->children.size == 0 && self->size.bytes > 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor += ts_tree__write_char_to_string(*writer, limit, self->lookahead_char);
    } else if (self->is_missing) {
      cursor += snprintf(*writer, limit, "(MISSING");
    } else {
      TSSymbol symbol = alias_symbol ? alias_symbol : self->symbol;
      const char *symbol_name = ts_language_symbol_name(language, symbol);
      cursor += snprintf(*writer, limit, "(%s", symbol_name);
    }
  }

  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self->alias_sequence_id);
  uint32_t structural_child_index = 0;
  for (uint32_t i = 0; i < self->children.size; i++) {
    Tree *child = self->children.contents[i];
    if (child->extra) {
      cursor += ts_tree__write_to_string(
        child, *writer, limit,
        language, false, include_all,
        0, false
      );
    } else {
      TSSymbol alias_symbol = alias_sequence ? alias_sequence[structural_child_index] : 0;
      cursor += ts_tree__write_to_string(
        child, *writer, limit,
        language, false, include_all,
        alias_symbol,
        alias_symbol ? ts_language_symbol_metadata(language, alias_symbol).named : false
      );
      structural_child_index++;
    }
  }

  if (visible) cursor += snprintf(*writer, limit, ")");

  return cursor - string;
}

char *ts_tree_string(const Tree *self, const TSLanguage *language, bool include_all) {
  char scratch_string[1];
  size_t size = ts_tree__write_to_string(
    self, scratch_string, 0,
    language, true,
    include_all, 0, false
  ) + 1;
  char *result = ts_malloc(size * sizeof(char));
  ts_tree__write_to_string(self, result, size, language, true, include_all, 0, false);
  return result;
}

void ts_tree__print_dot_graph(const Tree *self, uint32_t byte_offset,
                              const TSLanguage *language, TSSymbol alias_symbol, FILE *f) {
  TSSymbol symbol = alias_symbol ? alias_symbol : self->symbol;
  fprintf(f, "tree_%p [label=\"%s\"", self, ts_language_symbol_name(language, symbol));

  if (self->children.size == 0)
    fprintf(f, ", shape=plaintext");
  if (self->extra)
    fprintf(f, ", fontcolor=gray");

  fprintf(f, ", tooltip=\"address:%p\nrange:%u - %u\nstate:%d\nerror-cost:%u\nrepeat-depth:%u\"]\n",
          self, byte_offset, byte_offset + ts_tree_total_bytes(self), self->parse_state,
          self->error_cost, self->repeat_depth);

  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self->alias_sequence_id);
  uint32_t structural_child_index = 0;
  for (uint32_t i = 0; i < self->children.size; i++) {
    const Tree *child = self->children.contents[i];
    if (child->extra) {
      ts_tree__print_dot_graph(child, byte_offset, language, 0, f);
    } else {
      TSSymbol alias_symbol = alias_sequence ? alias_sequence[structural_child_index] : 0;
      ts_tree__print_dot_graph(child, byte_offset, language, alias_symbol, f);
      structural_child_index++;
    }
    fprintf(f, "tree_%p -> tree_%p [tooltip=%u]\n", self, child, i);
    byte_offset += ts_tree_total_bytes(child);
  }
}

void ts_tree_print_dot_graph(const Tree *self, const TSLanguage *language, FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "edge [arrowhead=none]\n");
  ts_tree__print_dot_graph(self, 0, language, 0, f);
  fprintf(f, "}\n");
}

static const TSExternalTokenState empty_state = {.length = 0, .short_data = {0}};

bool ts_tree_external_token_state_eq(const Tree *self, const Tree *other) {
  const TSExternalTokenState *state1 = &empty_state;
  const TSExternalTokenState *state2 = &empty_state;
  if (self && self->has_external_tokens) state1 = &self->external_token_state;
  if (other && other->has_external_tokens) state2 = &other->external_token_state;
  return ts_external_token_state_eq(state1, state2);
}
