#include <stdbool.h>
#include "runtime/subtree.h"
#include "runtime/tree.h"
#include "runtime/language.h"

typedef struct {
  const Subtree *parent;
  const TSTree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  const TSSymbol *alias_sequence;
} ChildIterator;

// TSNode - constructors

TSNode ts_node_new(const TSTree *tree, const Subtree *subtree, Length position, TSSymbol alias) {
  return (TSNode) {
    {position.bytes, position.extent.row, position.extent.column, alias},
    subtree,
    tree,
  };
}

static inline TSNode ts_node__null() {
  return ts_node_new(NULL, NULL, length_zero(), 0);
}

// TSNode - accessors

uint32_t ts_node_start_byte(TSNode self) {
  return self.context[0];
}

TSPoint ts_node_start_point(TSNode self) {
  return (TSPoint) {self.context[1], self.context[2]};
}

static inline uint32_t ts_node__alias(const TSNode *self) {
  return self->context[3];
}

static inline const Subtree *ts_node__subtree(TSNode self) {
  return self.id;
}

// ChildIterator

static inline ChildIterator ts_node_iterate_children(const TSNode *node) {
  const Subtree *subtree = ts_node__subtree(*node);
  const TSSymbol *alias_sequence = ts_language_alias_sequence(
    node->tree->language,
    subtree->alias_sequence_id
  );
  return (ChildIterator) {
    .tree = node->tree,
    .parent = subtree,
    .position = {ts_node_start_byte(*node), ts_node_start_point(*node)},
    .child_index = 0,
    .structural_child_index = 0,
    .alias_sequence = alias_sequence,
  };
}

static inline bool ts_node_child_iterator_next(ChildIterator *self, TSNode *result) {
  if (self->child_index == self->parent->children.size) return false;
  const Subtree *child = self->parent->children.contents[self->child_index];
  TSSymbol alias_symbol = 0;
  if (!child->extra) {
    if (self->alias_sequence) {
      alias_symbol = self->alias_sequence[self->structural_child_index];
    }
    self->structural_child_index++;
  }
  if (self->child_index > 0) {
    self->position = length_add(self->position, child->padding);
  }
  *result = ts_node_new(
    self->tree,
    child,
    self->position,
    alias_symbol
  );
  self->position = length_add(self->position, child->size);
  self->child_index++;
  return true;
}

// TSNode - private

static inline bool ts_node__is_relevant(TSNode self, bool include_anonymous) {
  const Subtree *tree = ts_node__subtree(self);
  if (include_anonymous) {
    return tree->visible || ts_node__alias(&self);
  } else {
    return (
      (tree->visible && tree->named) ||
      (
        ts_node__alias(&self) &&
        ts_language_symbol_metadata(
          self.tree->language,
          ts_node__alias(&self)
        ).named
      )
    );
  }
}

static inline uint32_t ts_node__relevant_child_count(TSNode self, bool include_anonymous) {
  const Subtree *tree = ts_node__subtree(self);
  if (tree->children.size > 0) {
    if (include_anonymous) {
      return tree->visible_child_count;
    } else {
      return tree->named_child_count;
    }
  } else {
    return 0;
  }
}

static inline TSNode ts_node__child(TSNode self, uint32_t child_index, bool include_anonymous) {
  TSNode result = self;
  bool did_descend = true;

  while (did_descend) {
    did_descend = false;

    TSNode child;
    uint32_t index = 0;
    ChildIterator iterator = ts_node_iterate_children(&result);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node__is_relevant(child, include_anonymous)) {
        if (index == child_index) {
          ts_tree_set_cached_parent(self.tree, &child, &self);
          return child;
        }
        index++;
      } else {
        uint32_t grandchild_index = child_index - index;
        uint32_t grandchild_count = ts_node__relevant_child_count(child, include_anonymous);
        if (grandchild_index < grandchild_count) {
          did_descend = true;
          result = child;
          child_index = grandchild_index;
          break;
        }
        index += grandchild_count;
      }
    }
  }

  return ts_node__null();
}

static inline TSNode ts_node__prev_sibling(TSNode self, bool include_anonymous) {
  uint32_t target_end_byte = ts_node_end_byte(self);

  TSNode node = ts_node_parent(self);
  TSNode earlier_node = ts_node__null();
  bool earlier_node_is_relevant = false;

  while (ts_node__subtree(node)) {
    TSNode earlier_child = ts_node__null();
    bool earlier_child_is_relevant = false;
    bool found_child_containing_target = false;

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (iterator.position.bytes >= target_end_byte) {
        found_child_containing_target = ts_node__subtree(child) != ts_node__subtree(self);
        break;
      }

      if (ts_node__is_relevant(child, include_anonymous)) {
        earlier_child = child;
        earlier_child_is_relevant = true;
      } else if (ts_node__relevant_child_count(child, include_anonymous) > 0) {
        earlier_child = child;
        earlier_child_is_relevant = false;
      }
    }

    if (found_child_containing_target) {
      if (!ts_node_is_null(earlier_child)) {
        earlier_node = earlier_child;
        earlier_node_is_relevant = earlier_child_is_relevant;
      }
      node = child;
    } else if (earlier_child_is_relevant) {
      return earlier_child;
    } else if (!ts_node_is_null(earlier_child)) {
      node = earlier_child;
    } else if (earlier_node_is_relevant) {
      return earlier_node;
    } else {
      node = earlier_node;
    }
  }

  return ts_node__null();
}

static inline TSNode ts_node__next_sibling(TSNode self, bool include_anonymous) {
  uint32_t target_end_byte = ts_node_end_byte(self);

  TSNode node = ts_node_parent(self);
  TSNode later_node = ts_node__null();
  bool later_node_is_relevant = false;

  while (ts_node__subtree(node)) {
    TSNode later_child = ts_node__null();
    bool later_child_is_relevant = false;
    TSNode child_containing_target = ts_node__null();

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (iterator.position.bytes < target_end_byte) continue;
      if (ts_node_start_byte(child) <= ts_node_start_byte(self)) {
        if (ts_node__subtree(child) != ts_node__subtree(self)) {
          child_containing_target = child;
        }
      } else if (ts_node__is_relevant(child, include_anonymous)) {
        later_child = child;
        later_child_is_relevant = true;
        break;
      } else if (ts_node__relevant_child_count(child, include_anonymous) > 0) {
        later_child = child;
        later_child_is_relevant = false;
        break;
      }
    }

    if (!ts_node_is_null(child_containing_target)) {
      if (!ts_node_is_null(later_child)) {
        later_node = later_child;
        later_node_is_relevant = later_child_is_relevant;
      }
      node = child_containing_target;
    } else if (later_child_is_relevant) {
      return later_child;
    } else if (!ts_node_is_null(later_child)) {
      node = later_child;
    } else if (later_node_is_relevant) {
      return later_node;
    } else {
      node = later_node;
    }
  }

  return ts_node__null();
}

static inline bool point_gt(TSPoint self, TSPoint other) {
  return self.row > other.row || (self.row == other.row && self.column > other.column);
}

static inline TSNode ts_node__first_child_for_byte(TSNode self, uint32_t goal,
                                                   bool include_anonymous) {
  TSNode node = self;
  bool did_descend = true;

  while (did_descend) {
    did_descend = false;

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node_end_byte(child) > goal) {
        if (ts_node__is_relevant(child, include_anonymous)) {
          return child;
        } else if (ts_node_child_count(child) > 0) {
          did_descend = true;
          node = child;
          break;
        }
      }
    }
  }

  return ts_node__null();
}

static inline TSNode ts_node__descendant_for_byte_range(TSNode self, uint32_t min,
                                                        uint32_t max,
                                                        bool include_anonymous) {
  TSNode node = self;
  TSNode last_visible_node = self;

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (iterator.position.bytes > max) {
        if (ts_node_start_byte(child) > min) break;
        node = child;
        if (ts_node__is_relevant(node, include_anonymous)) {
          ts_tree_set_cached_parent(self.tree, &child, &last_visible_node);
          last_visible_node = node;
        }
        did_descend = true;
        break;
      }
    }
  }

  return last_visible_node;
}

static inline TSNode ts_node__descendant_for_point_range(TSNode self, TSPoint min,
                                                         TSPoint max,
                                                         bool include_anonymous) {
  TSNode node = self;
  TSNode last_visible_node = self;

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (point_gt(iterator.position.extent, max)) {
        if (point_gt(ts_node_start_point(child), min)) break;
        node = child;
        if (ts_node__is_relevant(node, include_anonymous)) {
          ts_tree_set_cached_parent(self.tree, &child, &last_visible_node);
          last_visible_node = node;
        }
        did_descend = true;
        break;
      }
    }
  }

  return last_visible_node;
}

// TSNode - public

uint32_t ts_node_end_byte(TSNode self) {
  return ts_node_start_byte(self) + ts_node__subtree(self)->size.bytes;
}

TSPoint ts_node_end_point(TSNode self) {
  return point_add(ts_node_start_point(self), ts_node__subtree(self)->size.extent);
}

TSSymbol ts_node_symbol(TSNode self) {
  const Subtree *tree = ts_node__subtree(self);
  return ts_node__alias(&self) ? ts_node__alias(&self) : tree->symbol;
}

const char *ts_node_type(TSNode self) {
  return ts_language_symbol_name(self.tree->language, ts_node_symbol(self));
}

char *ts_node_string(TSNode self) {
  return ts_subtree_string(ts_node__subtree(self), self.tree->language, false);
}

bool ts_node_eq(TSNode self, TSNode other) {
  return self.tree == other.tree && self.id == other.id;
}

bool ts_node_is_null(TSNode self) {
  return ts_node__subtree(self) == NULL;
}

bool ts_node_is_named(TSNode self) {
  const Subtree *tree = ts_node__subtree(self);
  return ts_node__alias(&self)
    ? ts_language_symbol_metadata(self.tree->language, ts_node__alias(&self)).named
    : tree->named;
}

bool ts_node_is_missing(TSNode self) {
  const Subtree *tree = ts_node__subtree(self);
  return tree->is_missing;
}

bool ts_node_has_changes(TSNode self) {
  return ts_node__subtree(self)->has_changes;
}

bool ts_node_has_error(TSNode self) {
  return ts_node__subtree(self)->error_cost > 0;
}

TSNode ts_node_parent(TSNode self) {
  TSNode node = ts_tree_get_cached_parent(self.tree, &self);
  if (node.id) return node;

  node = ts_tree_root_node(self.tree);
  uint32_t end_byte = ts_node_end_byte(self);
  if (ts_node__subtree(node) == ts_node__subtree(self)) return ts_node__null();

  TSNode last_visible_node = node;
  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    TSNode child;
    ChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (
        ts_node_start_byte(child) > ts_node_start_byte(self) ||
        ts_node__subtree(child) == ts_node__subtree(self)
      ) break;
      if (iterator.position.bytes >= end_byte) {
        node = child;
        if (ts_node__is_relevant(child, true)) {
          ts_tree_set_cached_parent(self.tree, &node, &last_visible_node);
          last_visible_node = node;
        }
        did_descend = true;
        break;
      }
    }
  }

  return last_visible_node;
}

TSNode ts_node_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, true);
}

TSNode ts_node_named_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, false);
}

uint32_t ts_node_child_count(TSNode self) {
  const Subtree *tree = ts_node__subtree(self);
  if (tree->children.size > 0) {
    return tree->visible_child_count;
  } else {
    return 0;
  }
}

uint32_t ts_node_named_child_count(TSNode self) {
  const Subtree *tree = ts_node__subtree(self);
  if (tree->children.size > 0) {
    return tree->named_child_count;
  } else {
    return 0;
  }
}

TSNode ts_node_next_sibling(TSNode self) {
  return ts_node__next_sibling(self, true);
}

TSNode ts_node_next_named_sibling(TSNode self) {
  return ts_node__next_sibling(self, false);
}

TSNode ts_node_prev_sibling(TSNode self) {
  return ts_node__prev_sibling(self, true);
}

TSNode ts_node_prev_named_sibling(TSNode self) {
  return ts_node__prev_sibling(self, false);
}

TSNode ts_node_first_child_for_byte(TSNode self, uint32_t byte) {
  return ts_node__first_child_for_byte(self, byte, true);
}

TSNode ts_node_first_named_child_for_byte(TSNode self, uint32_t byte) {
  return ts_node__first_child_for_byte(self, byte, false);
}

TSNode ts_node_descendant_for_byte_range(TSNode self, uint32_t min, uint32_t max) {
  return ts_node__descendant_for_byte_range(self, min, max, true);
}

TSNode ts_node_named_descendant_for_byte_range(TSNode self, uint32_t min,
                                               uint32_t max) {
  return ts_node__descendant_for_byte_range(self, min, max, false);
}

TSNode ts_node_descendant_for_point_range(TSNode self, TSPoint min, TSPoint max) {
  return ts_node__descendant_for_point_range(self, min, max, true);
}

TSNode ts_node_named_descendant_for_point_range(TSNode self, TSPoint min,
                                                TSPoint max) {
  return ts_node__descendant_for_point_range(self, min, max, false);
}

void ts_node_edit(TSNode *self, const TSInputEdit *edit) {
  uint32_t start_byte = ts_node_start_byte(*self);
  TSPoint start_point = ts_node_start_point(*self);

  if (start_byte >= edit->old_end_byte) {
    start_byte = edit->new_end_byte + (start_byte - edit->old_end_byte);
    start_point = point_add(edit->new_end_point, point_sub(start_point, edit->old_end_point));
  } else if (start_byte > edit->start_byte) {
    start_byte = edit->new_end_byte;
    start_point = edit->new_end_point;
  }

  self->context[0] = start_byte;
  self->context[1] = start_point.row;
  self->context[2] = start_point.column;
}
