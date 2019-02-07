#include "tree_sitter/api.h"
#include "./alloc.h"
#include "./tree_cursor.h"
#include "./language.h"
#include "./tree.h"

typedef struct {
  Subtree parent;
  const TSTree *tree;
  Length position;
  uint32_t child_index;
  uint32_t child_info_offset;
} CursorChildIterator;

// CursorChildIterator

static inline CursorChildIterator ts_tree_cursor_iterate_children(const TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  if (ts_subtree_child_count(*last_entry->subtree) == 0) {
    return (CursorChildIterator) {NULL_SUBTREE, self->tree, length_zero(), 0, 0};
  }
  uint32_t child_info_offset =
    last_entry->subtree->ptr->child_info_sequence_id *
    self->tree->language->max_child_info_production_length;
  return (CursorChildIterator) {
    .tree = self->tree,
    .parent = *last_entry->subtree,
    .position = last_entry->position,
    .child_index = 0,
    .child_info_offset = child_info_offset,
  };
}

static inline bool ts_tree_cursor_child_iterator_next(CursorChildIterator *self,
                                                      TreeCursorEntry *result,
                                                      bool *visible) {
  if (!self->parent.ptr || self->child_index == self->parent.ptr->child_count) return false;
  const Subtree *child = &self->parent.ptr->children[self->child_index];
  *result = (TreeCursorEntry) {
    .subtree = child,
    .position = self->position,
    .child_index = self->child_index,
    .child_info_offset = self->child_info_offset,
  };
  *visible = ts_subtree_visible(*child);
  bool extra = ts_subtree_extra(*child);
  if (!extra && self->child_info_offset) {
    *visible |= self->tree->language->alias_sequences[self->child_info_offset];
    self->child_info_offset++;
  }

  self->position = length_add(self->position, ts_subtree_size(*child));
  self->child_index++;

  if (self->child_index < self->parent.ptr->child_count) {
    Subtree next_child = self->parent.ptr->children[self->child_index];
    self->position = length_add(self->position, ts_subtree_padding(next_child));
  }

  return true;
}

// TSTreeCursor - lifecycle

TSTreeCursor ts_tree_cursor_new(TSNode node) {
  TSTreeCursor self = {NULL, NULL, {0, 0}};
  ts_tree_cursor_init((TreeCursor *)&self, node);
  return self;
}

void ts_tree_cursor_reset(TSTreeCursor *_self, TSNode node) {
  ts_tree_cursor_init((TreeCursor *)_self, node);
}

void ts_tree_cursor_init(TreeCursor *self, TSNode node) {
  self->tree = node.tree;
  array_clear(&self->stack);
  array_push(&self->stack, ((TreeCursorEntry) {
    .subtree = (const Subtree *)node.id,
    .position = {
      ts_node_start_byte(node),
      ts_node_start_point(node)
    },
    .child_index = 0,
    .child_info_offset = 0,
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
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      if (visible) {
        array_push(&self->stack, entry);
        return true;
      }

      if (ts_subtree_visible_child_count(*entry.subtree) > 0) {
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
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      uint32_t end_byte = entry.position.bytes + ts_subtree_size(*entry.subtree).bytes;
      bool at_goal = end_byte > goal_byte;
      uint32_t visible_child_count = ts_subtree_visible_child_count(*entry.subtree);

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
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    iterator.child_index = entry.child_index;
    iterator.child_info_offset = entry.child_info_offset;
    iterator.position = entry.position;

    bool visible = false;
    ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible);
    if (visible && self->stack.size + 1 < initial_size) break;

    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      if (visible) {
        array_push(&self->stack, entry);
        return true;
      }

      if (ts_subtree_visible_child_count(*entry.subtree)) {
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
      is_aliased =
        entry->child_info_offset &&
        self->tree->language->alias_sequences[entry->child_info_offset];
    }
    if (ts_subtree_visible(*entry->subtree) || is_aliased) {
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
  if (last_entry->child_info_offset) {
    alias_symbol = self->tree->language->alias_sequences[last_entry->child_info_offset];
  }
  return ts_node_new(
    self->tree,
    last_entry->subtree,
    last_entry->position,
    alias_symbol
  );
}

TSFieldId ts_tree_cursor_current_field_id(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *entry = array_back(&self->stack);
  if (entry->child_info_offset) {
    return self->tree->language->field_sequences[entry->child_info_offset];
  } else {
    return 0;
  }
}

const char *ts_tree_cursor_current_field_name(const TSTreeCursor *_self) {
  TSFieldId id = ts_tree_cursor_current_field_id(_self);
  const TreeCursor *self = (const TreeCursor *)_self;
  return self->tree->language->field_names[id];
}
