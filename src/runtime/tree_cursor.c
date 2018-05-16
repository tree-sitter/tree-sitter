#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/tree_cursor.h"
#include "runtime/language.h"
#include "runtime/tree.h"

TSTreeCursor *ts_tree_cursor_new(const TSTree *tree) {
  TSTreeCursor *self = ts_malloc(sizeof(TSTreeCursor));
  ts_tree_cursor_init(self, tree);
  return self;
}

void ts_tree_cursor_init(TSTreeCursor *self, const TSTree *tree) {
  self->tree = tree;
  array_init(&self->stack);
  array_push(&self->stack, ((TreeCursorEntry) {
    .subtree = tree->root,
    .position = length_zero(),
    .child_index = 0,
    .structural_child_index = 0,
  }));
}

void ts_tree_cursor_delete(TSTreeCursor *self) {
  array_delete(&self->stack);
  ts_free(self);
}

bool ts_tree_cursor_goto_first_child(TSTreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  const Subtree *tree = last_entry->subtree;
  Length position = last_entry->position;

  bool did_descend;
  do {
    did_descend = false;

    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < tree->children.size; i++) {
      const Subtree *child = tree->children.contents[i];
      if (child->visible || child->visible_child_count > 0) {
        array_push(&self->stack, ((TreeCursorEntry) {
          .subtree = child,
          .child_index = i,
          .structural_child_index = structural_child_index,
          .position = position,
        }));

        if (child->visible) {
          return true;
        } else {
          tree = child;
          did_descend = true;
          break;
        }
      }
      if (!child->extra) structural_child_index++;
      position = length_add(position, ts_subtree_total_size(child));
    }
  } while (did_descend);

  return false;
}

int64_t ts_tree_cursor_goto_first_child_for_byte(TSTreeCursor *self, uint32_t goal_byte) {
  uint32_t initial_size = self->stack.size;
  TreeCursorEntry *last_entry = array_back(&self->stack);
  const Subtree *tree = last_entry->subtree;
  Length position = last_entry->position;
  uint32_t visible_child_index = 0;

  bool did_descend;
  do {
    did_descend = false;

    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < tree->children.size; i++) {
      const Subtree *child = tree->children.contents[i];
      Length next_position = length_add(position, ts_subtree_total_size(child));
      bool at_goal = next_position.bytes > goal_byte;

      if (at_goal) {
        if (child->visible || child->visible_child_count > 0) {
          array_push(&self->stack, ((TreeCursorEntry) {
            .subtree = child,
            .child_index = i,
            .structural_child_index = structural_child_index,
            .position = position,
          }));

          if (child->visible) {
            return visible_child_index;
          } else {
            tree = child;
            did_descend = true;
            break;
          }
        }
      } else {
        if (child->visible) {
          visible_child_index++;
        } else {
          visible_child_index += child->visible_child_count;
        }
      }

      if (!child->extra) structural_child_index++;
      position = next_position;
    }
  } while (did_descend);

  self->stack.size = initial_size;
  return -1;
}

bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *self) {
  TreeCursorEntry *child_entry = array_back(&self->stack);

  for (unsigned i = self->stack.size - 2; i + 1 > 0; i--) {
    TreeCursorEntry *parent_entry = &self->stack.contents[i];

    const Subtree *parent = parent_entry->subtree;
    uint32_t child_index = child_entry->child_index;
    uint32_t structural_child_index = child_entry->structural_child_index;
    Length position = child_entry->position;
    const Subtree *child = parent->children.contents[child_index];

    while (++child_index < parent->children.size) {
      if (!child->extra) structural_child_index++;
      position = length_add(position, ts_subtree_total_size(child));
      child = parent->children.contents[child_index];

      if (child->visible || child->visible_child_count > 0) {
        self->stack.contents[i + 1] = (TreeCursorEntry) {
          .subtree = child,
          .child_index = child_index,
          .structural_child_index = structural_child_index,
          .position = position,
        };
        self->stack.size = i + 2;

        if (child->visible) {
          return true;
        } else {
          ts_tree_cursor_goto_first_child(self);
          return true;
        }
      }
    }

    child_entry = parent_entry;
    if (parent->visible) break;
  }

  return false;
}

bool ts_tree_cursor_goto_parent(TSTreeCursor *self) {
  for (unsigned i = self->stack.size - 2; i + 1 > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    if (entry->subtree->visible) {
      self->stack.size = i + 1;
      return true;
    }
  }
  return false;
}

TSNode ts_tree_cursor_current_node(TSTreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  TSSymbol alias_symbol = 0;
  if (self->stack.size > 1) {
    TreeCursorEntry *parent_entry = &self->stack.contents[self->stack.size - 2];
    const TSSymbol *alias_sequence = ts_language_alias_sequence(
      self->tree->language,
      parent_entry->subtree->alias_sequence_id
    );
    if (alias_sequence) {
      alias_symbol = alias_sequence[last_entry->structural_child_index];
    }
  }
  return ts_node_new(self->tree, last_entry->subtree, last_entry->position, alias_symbol);
}
