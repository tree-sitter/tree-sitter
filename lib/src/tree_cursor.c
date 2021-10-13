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
  uint32_t structural_child_index;
  const TSSymbol *alias_sequence;
} CursorChildIterator;

// CursorChildIterator

static inline CursorChildIterator ts_tree_cursor_iterate_children(const TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->stack);
  if (ts_subtree_child_count(*last_entry->subtree) == 0) {
    return (CursorChildIterator) {NULL_SUBTREE, self->tree, length_zero(), 0, 0, NULL};
  }
  const TSSymbol *alias_sequence = ts_language_alias_sequence(
    self->tree->language,
    last_entry->subtree->ptr->production_id
  );
  return (CursorChildIterator) {
    .tree = self->tree,
    .parent = *last_entry->subtree,
    .position = last_entry->position,
    .child_index = 0,
    .structural_child_index = 0,
    .alias_sequence = alias_sequence,
  };
}

static inline bool ts_tree_cursor_child_iterator_next(
  CursorChildIterator *self,
  TreeCursorEntry *result,
  bool *visible
) {
  if (!self->parent.ptr || self->child_index == self->parent.ptr->child_count) return false;
  const Subtree *child = &ts_subtree_children(self->parent)[self->child_index];
  *result = (TreeCursorEntry) {
    .subtree = child,
    .position = self->position,
    .child_index = self->child_index,
    .structural_child_index = self->structural_child_index,
  };
  *visible = ts_subtree_visible(*child);
  bool extra = ts_subtree_extra(*child);
  if (!extra && self->alias_sequence) {
    *visible |= self->alias_sequence[self->structural_child_index];
    self->structural_child_index++;
  }

  self->position = length_add(self->position, ts_subtree_size(*child));
  self->child_index++;

  if (self->child_index < self->parent.ptr->child_count) {
    Subtree next_child = ts_subtree_children(self->parent)[self->child_index];
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

  self->stack.size = initial_size;
  return -1;
}

int64_t ts_tree_cursor_goto_first_child_for_point(TSTreeCursor *_self, TSPoint goal_point) {
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
      TSPoint end_point = point_add(entry.position.extent, ts_subtree_size(*entry.subtree).extent);
      bool at_goal = point_gt(end_point, goal_point);
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
    if (ts_subtree_visible(*entry->subtree)) {
      self->stack.size = i + 1;
      return true;
    }
    if (i > 0 && !ts_subtree_extra(*entry->subtree)) {
      TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
      if (ts_language_alias_at(
        self->tree->language,
        parent_entry->subtree->ptr->production_id,
        entry->structural_child_index
      )) {
        self->stack.size = i + 1;
        return true;
      }
    }
  }
  return false;
}

TSNode ts_tree_cursor_current_node(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *last_entry = array_back(&self->stack);
  TSSymbol alias_symbol = 0;
  if (self->stack.size > 1 && !ts_subtree_extra(*last_entry->subtree)) {
    TreeCursorEntry *parent_entry = &self->stack.contents[self->stack.size - 2];
    alias_symbol = ts_language_alias_at(
      self->tree->language,
      parent_entry->subtree->ptr->production_id,
      last_entry->structural_child_index
    );
  }
  return ts_node_new(
    self->tree,
    last_entry->subtree,
    last_entry->position,
    alias_symbol
  );
}

// Private - Get various facts about the current node that are needed
// when executing tree queries.
void ts_tree_cursor_current_status(
  const TSTreeCursor *_self,
  TSFieldId *field_id,
  bool *has_later_siblings,
  bool *has_later_named_siblings,
  bool *can_have_later_siblings_with_this_field,
  TSSymbol *supertypes,
  unsigned *supertype_count
) {
  const TreeCursor *self = (const TreeCursor *)_self;
  unsigned max_supertypes = *supertype_count;
  *field_id = 0;
  *supertype_count = 0;
  *has_later_siblings = false;
  *has_later_named_siblings = false;
  *can_have_later_siblings_with_this_field = false;

  // Walk up the tree, visiting the current node and its invisible ancestors,
  // because fields can refer to nodes through invisible *wrapper* nodes,
  for (unsigned i = self->stack.size - 1; i > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];

    const TSSymbol *alias_sequence = ts_language_alias_sequence(
      self->tree->language,
      parent_entry->subtree->ptr->production_id
    );

    #define subtree_symbol(subtree, structural_child_index) \
      ((                                                    \
        !ts_subtree_extra(subtree) &&                       \
        alias_sequence &&                                   \
        alias_sequence[structural_child_index]              \
      ) ?                                                   \
        alias_sequence[structural_child_index] :            \
        ts_subtree_symbol(subtree))

    // Stop walking up when a visible ancestor is found.
    TSSymbol entry_symbol = subtree_symbol(
      *entry->subtree,
      entry->structural_child_index
    );
    TSSymbolMetadata entry_metadata = ts_language_symbol_metadata(
      self->tree->language,
      entry_symbol
    );
    if (i != self->stack.size - 1 && entry_metadata.visible) break;

    // Record any supertypes
    if (entry_metadata.supertype && *supertype_count < max_supertypes) {
      supertypes[*supertype_count] = entry_symbol;
      (*supertype_count)++;
    }

    // Determine if the current node has later siblings.
    if (!*has_later_siblings) {
      unsigned sibling_count = parent_entry->subtree->ptr->child_count;
      unsigned structural_child_index = entry->structural_child_index;
      if (!ts_subtree_extra(*entry->subtree)) structural_child_index++;
      for (unsigned j = entry->child_index + 1; j < sibling_count; j++) {
        Subtree sibling = ts_subtree_children(*parent_entry->subtree)[j];
        TSSymbolMetadata sibling_metadata = ts_language_symbol_metadata(
          self->tree->language,
          subtree_symbol(sibling, structural_child_index)
        );
        if (sibling_metadata.visible) {
          *has_later_siblings = true;
          if (*has_later_named_siblings) break;
          if (sibling_metadata.named) {
            *has_later_named_siblings = true;
            break;
          }
        } else if (ts_subtree_visible_child_count(sibling) > 0) {
          *has_later_siblings = true;
          if (*has_later_named_siblings) break;
          if (sibling.ptr->named_child_count > 0) {
            *has_later_named_siblings = true;
            break;
          }
        }
        if (!ts_subtree_extra(sibling)) structural_child_index++;
      }
    }

    #undef subtree_symbol

    if (!ts_subtree_extra(*entry->subtree)) {
      const TSFieldMapEntry *field_map, *field_map_end;
      ts_language_field_map(
        self->tree->language,
        parent_entry->subtree->ptr->production_id,
        &field_map, &field_map_end
      );

      // Look for a field name associated with the current node.
      if (!*field_id) {
        for (const TSFieldMapEntry *i = field_map; i < field_map_end; i++) {
          if (!i->inherited && i->child_index == entry->structural_child_index) {
            *field_id = i->field_id;
            break;
          }
        }
      }

      // Determine if the current node can have later siblings with the same field name.
      if (*field_id) {
        for (const TSFieldMapEntry *i = field_map; i < field_map_end; i++) {
          if (
            i->field_id == *field_id &&
            i->child_index > entry->structural_child_index
          ) {
            *can_have_later_siblings_with_this_field = true;
            break;
          }
        }
      }
    }
  }
}

TSNode ts_tree_cursor_parent_node(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  for (int i = (int)self->stack.size - 2; i >= 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    bool is_visible = true;
    TSSymbol alias_symbol = 0;
    if (i > 0) {
      TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
      alias_symbol = ts_language_alias_at(
        self->tree->language,
        parent_entry->subtree->ptr->production_id,
        entry->structural_child_index
      );
      is_visible = (alias_symbol != 0) || ts_subtree_visible(*entry->subtree);
    }
    if (is_visible) {
      return ts_node_new(
        self->tree,
        entry->subtree,
        entry->position,
        alias_symbol
      );
    }
  }
  return ts_node_new(NULL, NULL, length_zero(), 0);
}

TSFieldId ts_tree_cursor_current_field_id(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;

  // Walk up the tree, visiting the current node and its invisible ancestors.
  for (unsigned i = self->stack.size - 1; i > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];

    // Stop walking up when another visible node is found.
    if (i != self->stack.size - 1) {
      if (ts_subtree_visible(*entry->subtree)) break;
      if (
        !ts_subtree_extra(*entry->subtree) &&
        ts_language_alias_at(
          self->tree->language,
          parent_entry->subtree->ptr->production_id,
          entry->structural_child_index
        )
      ) break;
    }

    if (ts_subtree_extra(*entry->subtree)) break;

    const TSFieldMapEntry *field_map, *field_map_end;
    ts_language_field_map(
      self->tree->language,
      parent_entry->subtree->ptr->production_id,
      &field_map, &field_map_end
    );
    for (const TSFieldMapEntry *i = field_map; i < field_map_end; i++) {
      if (!i->inherited && i->child_index == entry->structural_child_index) {
        return i->field_id;
      }
    }
  }
  return 0;
}

const char *ts_tree_cursor_current_field_name(const TSTreeCursor *_self) {
  TSFieldId id = ts_tree_cursor_current_field_id(_self);
  if (id) {
    const TreeCursor *self = (const TreeCursor *)_self;
    return self->tree->language->field_names[id];
  } else {
    return NULL;
  }
}

TSTreeCursor ts_tree_cursor_copy(const TSTreeCursor *_cursor) {
  const TreeCursor *cursor = (const TreeCursor *)_cursor;
  TSTreeCursor res = {NULL, NULL, {0, 0}};
  TreeCursor *copy = (TreeCursor *)&res;
  copy->tree = cursor->tree;
  array_init(&copy->stack);
  array_push_all(&copy->stack, &cursor->stack);
  return res;
}
