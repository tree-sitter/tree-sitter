#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/tree_cursor.h"
#include "runtime/document.h"
#include "runtime/language.h"

TSTreeCursor *ts_tree_cursor_new(const TSDocument *document) {
  TSTreeCursor *self = ts_malloc(sizeof(TSTreeCursor));
  self->document = document;
  array_init(&self->stack);
  array_push(&self->stack, ((TreeCursorEntry) {
    .tree = document->tree,
    .position = length_zero(),
    .child_index = 0,
    .structural_child_index = 0,
  }));
  return self;
}

void ts_tree_cursor_delete(TSTreeCursor *self) {
  array_delete(&self->stack);
  ts_free(self);
}

bool ts_tree_cursor_goto_first_child(TSTreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  Tree *tree = last_entry->tree;
  Length position = last_entry->position;

  bool did_descend;
  do {
    did_descend = false;

    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < tree->children.size; i++) {
      Tree *child = tree->children.contents[i];
      if (child->visible || child->visible_child_count > 0) {
        array_push(&self->stack, ((TreeCursorEntry) {
          .tree = child,
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
      position = length_add(position, ts_tree_total_size(child));
    }
  } while (did_descend);

  return false;
}

bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *self) {
  TreeCursorEntry *child_entry = array_back(&self->stack);

  for (unsigned i = self->stack.size - 2; i + 1 > 0; i--) {
    TreeCursorEntry *parent_entry = &self->stack.contents[i];

    Tree *parent = parent_entry->tree;
    uint32_t child_index = child_entry->child_index;
    uint32_t structural_child_index = child_entry->structural_child_index;
    Length position = child_entry->position;
    Tree *child = parent->children.contents[child_index];

    while (++child_index < parent->children.size) {
      if (!child->extra) structural_child_index++;
      position = length_add(position, ts_tree_total_size(child));
      child = parent->children.contents[child_index];

      if (child->visible || child->visible_child_count > 0) {
        self->stack.contents[i + 1] = (TreeCursorEntry) {
          .tree = child,
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
    if (entry->tree->visible) {
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
      self->document->parser.language,
      parent_entry->tree->alias_sequence_id
    );
    if (alias_sequence) {
      alias_symbol = alias_sequence[last_entry->structural_child_index];
    }
  }
  return (TSNode) {
    .document = self->document,
    .subtree = last_entry->tree,
    .position = last_entry->position.extent,
    .byte = last_entry->position.bytes,
    .alias_symbol = alias_symbol,
  };
}
