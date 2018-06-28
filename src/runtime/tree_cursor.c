#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/tree_cursor.h"
#include "runtime/language.h"
#include "runtime/tree.h"

typedef struct {
  const Subtree *parent;
  const TSTree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  const TSSymbol *alias_sequence;
} ChildIterator;

// ChildIterator

static inline ChildIterator ts_tree_cursor_iterate_children(const TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  const TSSymbol *alias_sequence = ts_language_alias_sequence(
    self->tree->language,
    last_entry->subtree->alias_sequence_id
  );
  return (ChildIterator) {
    .tree = self->tree,
    .parent = last_entry->subtree,
    .position = last_entry->position,
    .child_index = 0,
    .structural_child_index = 0,
    .alias_sequence = alias_sequence,
  };
}

static inline bool ts_tree_cursor_child_iterator_next(ChildIterator *self,
                                                      TreeCursorEntry *result,
                                                      bool *visible) {
  if (self->child_index == self->parent->children.size) return false;
  const Subtree *child = self->parent->children.contents[self->child_index];
  *result = (TreeCursorEntry) {
    .subtree = child,
    .position = self->position,
    .child_index = self->child_index,
    .structural_child_index = self->structural_child_index,
  };
  *visible = child->visible;
  if (!child->extra && self->alias_sequence) {
    *visible |= self->alias_sequence[self->structural_child_index];
  }

  self->position = length_add(self->position, child->size);
  self->child_index++;
  if (!child->extra) self->structural_child_index++;

  if (self->child_index < self->parent->children.size) {
    const Subtree *child = self->parent->children.contents[self->child_index];
    self->position = length_add(self->position, child->padding);
  }

  return true;
}

// TSTreeCursor - lifecycle

TSTreeCursor ts_tree_cursor_new(TSNode node) {
  TSTreeCursor self;
  ts_tree_cursor_init((TreeCursor *)&self, node);
  return self;
}

void ts_tree_cursor_init(TreeCursor *self, TSNode node) {
  self->tree = node.tree;
  array_init(&self->stack);
  array_push(&self->stack, ((TreeCursorEntry) {
    .subtree = (const Subtree *)node.id,
    .position = {
      ts_node_start_byte(node),
      ts_node_start_point(node)
    },
    .child_index = 0,
    .structural_child_index = 0,
  }));
}

void ts_tree_cursor_delete(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  array_delete(&self->stack);
}

// TSTreeCursor - walking the tree

bool ts_tree_cursor_goto_first_child(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;

  bool did_descend;
  do {
    did_descend = false;

    bool visible;
    TreeCursorEntry entry;
    ChildIterator iterator = ts_tree_cursor_iterate_children(self);
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      if (visible) {
        array_push(&self->stack, entry);
        return true;
      }

      if (entry.subtree->children.size > 0 && entry.subtree->visible_child_count > 0) {
        array_push(&self->stack, entry);
        did_descend = true;
        break;
      }
    }
  } while (did_descend);

  return false;
}

int64_t ts_tree_cursor_goto_first_child_for_byte(TSTreeCursor *_self, uint32_t goal_byte) {
  TreeCursor *self = (TreeCursor *)_self;
  uint32_t initial_size = self->stack.size;
  uint32_t visible_child_index = 0;

  bool did_descend;
  do {
    did_descend = false;

    bool visible;
    TreeCursorEntry entry;
    ChildIterator iterator = ts_tree_cursor_iterate_children(self);
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      uint32_t end_byte = entry.position.bytes + entry.subtree->size.bytes;
      bool at_goal = end_byte > goal_byte;
      uint32_t visible_child_count = entry.subtree->children.size > 0
        ? entry.subtree->visible_child_count
        : 0;

      if (at_goal) {
        if (visible) {
          array_push(&self->stack, entry);
          return visible_child_index;
        }

        if (visible_child_count > 0) {
          array_push(&self->stack, entry);
          did_descend = true;
          break;
        }
      } else if (visible) {
        visible_child_index++;
      } else {
        visible_child_index += visible_child_count;
      }
    }
  } while (did_descend);

  if (self->stack.size > initial_size &&
      ts_tree_cursor_goto_next_sibling((TSTreeCursor *)self)) {
    return visible_child_index;
  }

  self->stack.size = initial_size;
  return -1;
}

bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  uint32_t initial_size = self->stack.size;

  while (self->stack.size > 1) {
    TreeCursorEntry entry = array_pop(&self->stack);
    ChildIterator iterator = ts_tree_cursor_iterate_children(self);
    iterator.child_index = entry.child_index;
    iterator.structural_child_index = entry.structural_child_index;
    iterator.position = entry.position;

    bool visible = false;
    ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible);
    if (visible && self->stack.size + 1 < initial_size) break;

    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      if (visible) {
        array_push(&self->stack, entry);
        return true;
      }

      if (entry.subtree->children.size > 0 && entry.subtree->visible_child_count > 0) {
        array_push(&self->stack, entry);
        ts_tree_cursor_goto_first_child(_self);
        return true;
      }
    }
  }

  self->stack.size = initial_size;
  return false;
}

bool ts_tree_cursor_goto_parent(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  for (unsigned i = self->stack.size - 2; i + 1 > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    bool is_aliased = false;
    if (i > 0) {
      TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
      const TSSymbol *alias_sequence = ts_language_alias_sequence(
        self->tree->language,
        parent_entry->subtree->alias_sequence_id
      );
      is_aliased = alias_sequence && alias_sequence[entry->structural_child_index];
    }
    if (entry->subtree->visible || is_aliased) {
      self->stack.size = i + 1;
      return true;
    }
  }
  return false;
}

TSNode ts_tree_cursor_current_node(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *last_entry = array_back(&self->stack);
  TSSymbol alias_symbol = 0;
  if (self->stack.size > 1) {
    TreeCursorEntry *parent_entry = &self->stack.contents[self->stack.size - 2];
    const TSSymbol *alias_sequence = ts_language_alias_sequence(
      self->tree->language,
      parent_entry->subtree->alias_sequence_id
    );
    if (alias_sequence && !last_entry->subtree->extra) {
      alias_symbol = alias_sequence[last_entry->structural_child_index];
    }
  }
  return ts_node_new(
    self->tree,
    last_entry->subtree,
    last_entry->position,
    alias_symbol
  );
}
