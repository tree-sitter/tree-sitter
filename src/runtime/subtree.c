#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "runtime/alloc.h"
#include "runtime/atomic.h"
#include "runtime/subtree.h"
#include "runtime/length.h"
#include "runtime/language.h"
#include "runtime/error_costs.h"

typedef struct {
  Length start;
  Length old_end;
  Length new_end;
} Edit;

TSStateId TS_TREE_STATE_NONE = USHRT_MAX;

static const uint32_t MAX_TREE_POOL_SIZE = 1024;

static const ExternalScannerState empty_state = {.length = 0, .short_data = {0}};

// ExternalScannerState

void ts_external_scanner_state_init(ExternalScannerState *self, const char *data, unsigned length) {
  self->length = length;
  if (length > sizeof(self->short_data)) {
    self->long_data = ts_malloc(length);
    memcpy(self->long_data, data, length);
  } else {
    memcpy(self->short_data, data, length);
  }
}

ExternalScannerState ts_external_scanner_state_copy(const ExternalScannerState *self) {
  ExternalScannerState result = *self;
  if (self->length > sizeof(self->short_data)) {
    result.long_data = ts_malloc(self->length);
    memcpy(result.long_data, self->long_data, self->length);
  }
  return result;
}

void ts_external_scanner_state_delete(ExternalScannerState *self) {
  if (self->length > sizeof(self->short_data)) {
    ts_free(self->long_data);
  }
}

const char *ts_external_scanner_state_data(const ExternalScannerState *self) {
  if (self->length > sizeof(self->short_data)) {
    return self->long_data;
  } else {
    return self->short_data;
  }
}

bool ts_external_scanner_state_eq(const ExternalScannerState *a, const ExternalScannerState *b) {
  return a == b || (
    a->length == b->length &&
    !memcmp(ts_external_scanner_state_data(a), ts_external_scanner_state_data(b), a->length)
  );
}

// SubtreeArray

void ts_subtree_array_copy(SubtreeArray self, SubtreeArray *dest) {
  dest->size = self.size;
  dest->capacity = self.capacity;
  dest->contents = self.contents;
  if (self.capacity > 0) {
    dest->contents = ts_calloc(self.capacity, sizeof(Subtree *));
    memcpy(dest->contents, self.contents, self.size * sizeof(Subtree *));
    for (uint32_t i = 0; i < self.size; i++) {
      ts_subtree_retain(dest->contents[i]);
    }
  }
}

void ts_subtree_array_delete(SubtreePool *pool, SubtreeArray *self) {
  for (uint32_t i = 0; i < self->size; i++) {
    ts_subtree_release(pool, self->contents[i]);
  }
  array_delete(self);
}

SubtreeArray ts_subtree_array_remove_trailing_extras(SubtreeArray *self) {
  SubtreeArray result = array_new();

  uint32_t i = self->size - 1;
  for (; i + 1 > 0; i--) {
    const Subtree *child = self->contents[i];
    if (!child->extra) break;
    array_push(&result, child);
  }

  self->size = i + 1;
  ts_subtree_array_reverse(&result);
  return result;
}

void ts_subtree_array_reverse(SubtreeArray *self) {
  for (uint32_t i = 0, limit = self->size / 2; i < limit; i++) {
    size_t reverse_index = self->size - 1 - i;
    const Subtree *swap = self->contents[i];
    self->contents[i] = self->contents[reverse_index];
    self->contents[reverse_index] = swap;
  }
}

// SubtreePool

SubtreePool ts_subtree_pool_new(uint32_t capacity) {
  SubtreePool self = {array_new(), array_new()};
  array_reserve(&self.free_trees, capacity);
  return self;
}

void ts_subtree_pool_delete(SubtreePool *self) {
  if (self->free_trees.contents) {
    for (unsigned i = 0; i < self->free_trees.size; i++) {
      ts_free(self->free_trees.contents[i]);
    }
    array_delete(&self->free_trees);
  }
  if (self->tree_stack.contents) array_delete(&self->tree_stack);
}

Subtree *ts_subtree_pool_allocate(SubtreePool *self) {
  if (self->free_trees.size > 0) {
    return array_pop(&self->free_trees);
  } else {
    return ts_malloc(sizeof(Subtree));
  }
}

void ts_subtree_pool_free(SubtreePool *self, Subtree *tree) {
  if (self->free_trees.capacity > 0 && self->free_trees.size < MAX_TREE_POOL_SIZE) {
    array_push(&self->free_trees, tree);
  } else {
    ts_free(tree);
  }
}

// Subtree

Subtree *ts_subtree_new_leaf(SubtreePool *pool, TSSymbol symbol, Length padding, Length size,
                             const TSLanguage *language) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  Subtree *result = ts_subtree_pool_allocate(pool);
  *result = (Subtree){
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
    .is_keyword = false,
    .first_leaf = {
      .symbol = symbol,
      .lex_mode = {0, 0},
    },
    .has_external_tokens = false,
  };
  if (symbol == ts_builtin_sym_end) result->extra = true;
  return result;
}

Subtree *ts_subtree_new_error(SubtreePool *pool, Length size, Length padding,
                              int32_t lookahead_char, const TSLanguage *language) {
  Subtree *result = ts_subtree_new_leaf(pool, ts_builtin_sym_error, padding, size, language);
  result->fragile_left = true;
  result->fragile_right = true;
  result->lookahead_char = lookahead_char;
  return result;
}

Subtree *ts_subtree_new_copy(SubtreePool *pool, const Subtree *self) {
  Subtree *result = ts_subtree_pool_allocate(pool);
  *result = *self;
  if (result->children.size > 0) {
    ts_subtree_array_copy(self->children, &result->children);
  } else if (result->has_external_tokens) {
    result->external_scanner_state = ts_external_scanner_state_copy(&self->external_scanner_state);
  }
  result->ref_count = 1;
  return result;
}

Subtree *ts_subtree_make_mut(SubtreePool *pool, const Subtree *self) {
  if (self->ref_count == 1) {
    return (Subtree *)self;
  } else {
    Subtree *result = ts_subtree_new_copy(pool, self);
    ts_subtree_release(pool, self);
    return result;
  }
}

static void ts_subtree__compress(Subtree *self, unsigned count, const TSLanguage *language,
                                 MutableSubtreeArray *stack) {
  unsigned initial_stack_size = stack->size;

  Subtree *tree = self;
  for (unsigned i = 0; i < count; i++) {
    if (tree->ref_count > 1 || tree->children.size != 2) break;

    Subtree *child = (Subtree *)tree->children.contents[0];
    if (
      child->ref_count > 1 ||
      child->children.size != 2 ||
      child->symbol != tree->symbol
    ) break;

    Subtree *grandchild = (Subtree *)child->children.contents[0];
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
    assert(tree);
    Subtree *child = (Subtree *)tree->children.contents[0];
    Subtree *grandchild = (Subtree *)child->children.contents[1];
    ts_subtree_set_children(grandchild, &grandchild->children, language);
    ts_subtree_set_children(child, &child->children, language);
    ts_subtree_set_children(tree, &tree->children, language);
  }
}

void ts_subtree_balance(const Subtree *self, SubtreePool *pool, const TSLanguage *language) {
  array_clear(&pool->tree_stack);

  if (self->ref_count == 1) {
    array_push(&pool->tree_stack, (Subtree *)self);
  }

  while (pool->tree_stack.size > 0) {
    Subtree *tree = array_pop(&pool->tree_stack);
    assert(tree);

    if (tree->repeat_depth > 0 &&
        tree->children.contents[0]->repeat_depth > tree->children.contents[1]->repeat_depth) {
      unsigned n = (
        tree->children.contents[0]->repeat_depth -
        tree->children.contents[1]->repeat_depth
      );
      for (unsigned i = n / 2; i > 0; i /= 2) {
        ts_subtree__compress(tree, i, language, &pool->tree_stack);
        n -= i;
      }
    }

    for (uint32_t i = 0; i < tree->children.size; i++) {
      const Subtree *child = tree->children.contents[i];
      if (child->ref_count == 1) {
        array_push(&pool->tree_stack, (Subtree *)child);
      }
    }
  }
}

void ts_subtree_set_children(Subtree *self, SubtreeArray *children, const TSLanguage *language) {
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
    const Subtree *child = self->children.contents[i];

    if (i == 0) {
      self->padding = child->padding;
      self->size = child->size;
      self->bytes_scanned = child->bytes_scanned;
    } else {
      uint32_t bytes_scanned = ts_subtree_total_bytes(self) + child->bytes_scanned;
      if (bytes_scanned > self->bytes_scanned) self->bytes_scanned = bytes_scanned;
      self->size = length_add(self->size, ts_subtree_total_size(child));
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
      const Subtree *child = self->children.contents[i];
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
    const Subtree *first_child = self->children.contents[0];
    const Subtree *last_child = self->children.contents[self->children.size - 1];
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

Subtree *ts_subtree_new_node(SubtreePool *pool, TSSymbol symbol, SubtreeArray *children,
                             unsigned alias_sequence_id, const TSLanguage *language) {
  Subtree *result = ts_subtree_new_leaf(pool, symbol, length_zero(), length_zero(), language);
  result->alias_sequence_id = alias_sequence_id;
  if (symbol == ts_builtin_sym_error || symbol == ts_builtin_sym_error_repeat) {
    result->fragile_left = true;
    result->fragile_right = true;
  }
  ts_subtree_set_children(result, children, language);
  return result;
}

Subtree *ts_subtree_new_error_node(SubtreePool *pool, SubtreeArray *children,
                                   const TSLanguage *language) {
  return ts_subtree_new_node(pool, ts_builtin_sym_error, children, 0, language);
}

Subtree *ts_subtree_new_missing_leaf(SubtreePool *pool, TSSymbol symbol,
                                     const TSLanguage *language) {
  Subtree *result = ts_subtree_new_leaf(pool, symbol, length_zero(), length_zero(), language);
  result->is_missing = true;
  result->error_cost = ERROR_COST_PER_MISSING_TREE + ERROR_COST_PER_RECOVERY;
  return result;
}

void ts_subtree_retain(const Subtree *self) {
  assert(self->ref_count > 0);
  atomic_inc((volatile uint32_t *)&self->ref_count);
  assert(self->ref_count != 0);
}

void ts_subtree_release(SubtreePool *pool, const Subtree *self) {
  array_clear(&pool->tree_stack);

  assert(self->ref_count > 0);
  if (atomic_dec((volatile uint32_t *)&self->ref_count) == 0) {
    array_push(&pool->tree_stack, (Subtree *)self);
  }

  while (pool->tree_stack.size > 0) {
    Subtree *tree = array_pop(&pool->tree_stack);
    if (tree->children.size > 0) {
      for (uint32_t i = 0; i < tree->children.size; i++) {
        const Subtree *child = tree->children.contents[i];
        if (atomic_dec((volatile uint32_t *)&child->ref_count) == 0) {
          array_push(&pool->tree_stack, (Subtree *)child);
        }
      }
      array_delete(&tree->children);
    } else if (tree->has_external_tokens) {
      ts_external_scanner_state_delete(&tree->external_scanner_state);
    }
    ts_subtree_pool_free(pool, tree);
  }
}

bool ts_subtree_eq(const Subtree *self, const Subtree *other) {
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
    if (!ts_subtree_eq(self->children.contents[i], other->children.contents[i])) {
      return false;
    }
  }
  return true;
}

int ts_subtree_compare(const Subtree *left, const Subtree *right) {
  if (left->symbol < right->symbol)
    return -1;
  if (right->symbol < left->symbol)
    return 1;
  if (left->children.size < right->children.size)
    return -1;
  if (right->children.size < left->children.size)
    return 1;
  for (uint32_t i = 0; i < left->children.size; i++) {
    const Subtree *left_child = left->children.contents[i];
    const Subtree *right_child = right->children.contents[i];
    switch (ts_subtree_compare(left_child, right_child)) {
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

const Subtree *ts_subtree_edit(const Subtree *self, const TSInputEdit *edit, SubtreePool *pool) {
  typedef struct {
    const Subtree **tree;
    Edit edit;
  } StackEntry;

  Array(StackEntry) stack = array_new();
  array_push(&stack, ((StackEntry) {
    .tree = &self,
    .edit = (Edit) {
      .start = {edit->start_byte, edit->start_point},
      .old_end = {edit->old_end_byte, edit->old_end_point},
      .new_end = {edit->new_end_byte, edit->new_end_point},
    },
  }));

  while (stack.size) {
    StackEntry entry = array_pop(&stack);
    Edit edit = entry.edit;
    bool is_noop = edit.old_end.bytes == edit.start.bytes && edit.new_end.bytes == edit.start.bytes;
    bool is_pure_insertion = edit.old_end.bytes == edit.start.bytes;
    if (is_noop && edit.start.bytes >= (*entry.tree)->bytes_scanned) continue;

    Subtree *result = ts_subtree_make_mut(pool, *entry.tree);
    *entry.tree = result;

    // If the edit is entirely within the space before this subtree, then shift this
    // subtree over according to the edit without changing its size.
    if (edit.old_end.bytes <= result->padding.bytes) {
      result->padding = length_add(edit.new_end, length_sub(result->padding, edit.old_end));
    }

    // If the edit starts in the space before this subtree and extends into this subtree,
    // shrink the subtree's content to compensate for the change in the space before it.
    else if (edit.start.bytes < result->padding.bytes) {
      result->size = length_sub(result->size, length_sub(edit.old_end, result->padding));
      result->padding = edit.new_end;
    }

    // If the edit is a pure insertion right at the start of the subtree,
    // shift the subtree over according to the insertion.
    else if (edit.start.bytes == result->padding.bytes && is_pure_insertion) {
      result->padding = edit.new_end;
    }

    // If the edit is within this subtree, resize the subtree to reflect the edit.
    else {
      uint32_t total_bytes = ts_subtree_total_bytes(*entry.tree);
      if (edit.start.bytes < total_bytes ||
         (edit.start.bytes == total_bytes && is_pure_insertion)) {
        result->size = length_add(
          length_sub(edit.new_end, result->padding),
          length_sub(result->size, length_sub(edit.old_end, result->padding))
        );
      }
    }

    result->has_changes = true;

    Length child_left, child_right = length_zero();
    for (uint32_t i = 0; i < result->children.size; i++) {
      const Subtree **child = &result->children.contents[i];
      Length child_size = ts_subtree_total_size(*child);
      child_left = child_right;
      child_right = length_add(child_left, child_size);

      // If this child starts after the edit, then we're done processing children.
      if (child_left.bytes > edit.old_end.bytes ||
          (child_left.bytes == edit.old_end.bytes && child_size.bytes > 0 && i > 0)) break;

      // Transform edit into the child's coordinate space.
      Edit child_edit = {
        .start = length_sub(edit.start, child_left),
        .old_end = length_sub(edit.old_end, child_left),
        .new_end = length_sub(edit.new_end, child_left),
      };

      // Clamp child_edit to the child's bounds.
      if (edit.start.bytes < child_left.bytes) child_edit.start = length_zero();
      if (edit.old_end.bytes < child_left.bytes) child_edit.old_end = length_zero();
      if (edit.new_end.bytes < child_left.bytes) child_edit.new_end = length_zero();
      if (edit.old_end.bytes > child_right.bytes) child_edit.old_end = child_size;

      // Interpret all inserted text as applying to the *first* child that touches the edit.
      // Subsequent children are only never have any text inserted into them; they are only
      // shrunk to compensate for the edit.
      if (child_right.bytes > edit.start.bytes ||
          (child_right.bytes == edit.start.bytes && is_pure_insertion)) {
        edit.new_end = edit.start;
      }

      // Children that occur before the edit are not reshaped by the edit.
      else {
        child_edit.old_end = child_edit.start;
        child_edit.new_end = child_edit.start;
      }

      // Queue processing of this child's subtree.
      array_push(&stack, ((StackEntry) {
        .tree = child,
        .edit = child_edit,
      }));
    }
  }

  array_delete(&stack);
  return self;
}

const Subtree *ts_subtree_last_external_token(const Subtree *tree) {
  if (!tree->has_external_tokens) return NULL;
  while (tree->children.size > 0) {
    for (uint32_t i = tree->children.size - 1; i + 1 > 0; i--) {
      const Subtree *child = tree->children.contents[i];
      if (child->has_external_tokens) {
        tree = child;
        break;
      }
    }
  }
  return tree;
}

static size_t ts_subtree__write_char_to_string(char *s, size_t n, int32_t c) {
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

static size_t ts_subtree__write_to_string(const Subtree *self, char *string, size_t limit,
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
      cursor += ts_subtree__write_char_to_string(*writer, limit, self->lookahead_char);
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
    const Subtree *child = self->children.contents[i];
    if (child->extra) {
      cursor += ts_subtree__write_to_string(
        child, *writer, limit,
        language, false, include_all,
        0, false
      );
    } else {
      TSSymbol alias_symbol = alias_sequence ? alias_sequence[structural_child_index] : 0;
      cursor += ts_subtree__write_to_string(
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

char *ts_subtree_string(const Subtree *self, const TSLanguage *language, bool include_all) {
  char scratch_string[1];
  size_t size = ts_subtree__write_to_string(
    self, scratch_string, 0,
    language, true,
    include_all, 0, false
  ) + 1;
  char *result = ts_malloc(size * sizeof(char));
  ts_subtree__write_to_string(self, result, size, language, true, include_all, 0, false);
  return result;
}

void ts_subtree__print_dot_graph(const Subtree *self, uint32_t byte_offset,
                              const TSLanguage *language, TSSymbol alias_symbol, FILE *f) {
  TSSymbol symbol = alias_symbol ? alias_symbol : self->symbol;
  fprintf(f, "tree_%p [label=\"%s\"", self, ts_language_symbol_name(language, symbol));

  if (self->children.size == 0)
    fprintf(f, ", shape=plaintext");
  if (self->extra)
    fprintf(f, ", fontcolor=gray");

  fprintf(f, ", tooltip=\""
    "address:%p\n"
    "range:%u - %u\n"
    "state:%d\n"
    "error-cost:%u\n"
    "repeat-depth:%u\n"
    "bytes-scanned:%u\"]\n",
    self,
    byte_offset, byte_offset + ts_subtree_total_bytes(self),
    self->parse_state,
    self->error_cost,
    self->repeat_depth,
    self->bytes_scanned
  );

  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self->alias_sequence_id);
  uint32_t structural_child_index = 0;
  for (uint32_t i = 0; i < self->children.size; i++) {
    const Subtree *child = self->children.contents[i];
    if (child->extra) {
      ts_subtree__print_dot_graph(child, byte_offset, language, 0, f);
    } else {
      TSSymbol alias_symbol = alias_sequence ? alias_sequence[structural_child_index] : 0;
      ts_subtree__print_dot_graph(child, byte_offset, language, alias_symbol, f);
      structural_child_index++;
    }
    fprintf(f, "tree_%p -> tree_%p [tooltip=%u]\n", self, child, i);
    byte_offset += ts_subtree_total_bytes(child);
  }
}

void ts_subtree_print_dot_graph(const Subtree *self, const TSLanguage *language, FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "edge [arrowhead=none]\n");
  ts_subtree__print_dot_graph(self, 0, language, 0, f);
  fprintf(f, "}\n");
}

bool ts_subtree_external_scanner_state_eq(const Subtree *self, const Subtree *other) {
  const ExternalScannerState *state1 = &empty_state;
  const ExternalScannerState *state2 = &empty_state;
  if (self && self->has_external_tokens) state1 = &self->external_scanner_state;
  if (other && other->has_external_tokens) state2 = &other->external_scanner_state;
  return ts_external_scanner_state_eq(state1, state2);
}
