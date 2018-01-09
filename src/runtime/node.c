#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const Tree *tree, uint32_t byte, uint32_t row) {
  return (TSNode){.data = tree, .offset = { byte, row } };
}

/*
 *  Private
 */

static inline TSNode ts_node__null() {
  return ts_node_make(NULL, 0, 0);
}

static inline const Tree *ts_node__tree(TSNode self) {
  return self.data;
}

static inline uint32_t ts_node__offset_byte(TSNode self) {
  return self.offset[0];
}

static inline uint32_t ts_node__offset_row(TSNode self) {
  return self.offset[1];
}

static inline bool ts_node__is_relevant(TSNode self, bool include_anonymous) {
  const Tree *tree = ts_node__tree(self);
  if (include_anonymous) {
    return tree->context.alias_symbol || tree->visible;
  } else {
    return tree->context.alias_is_named || (tree->visible && tree->named);
  }
}

static inline uint32_t ts_node__relevant_child_count(TSNode self,
                                                   bool include_anonymous) {
  const Tree *tree = ts_node__tree(self);
  if (tree->child_count > 0) {
    if (include_anonymous) {
      return tree->visible_child_count;
    } else {
      return tree->named_child_count;
    }
  } else {
    return 0;
  }
}

static inline TSNode ts_node__direct_parent(TSNode self, uint32_t *index) {
  const Tree *tree = ts_node__tree(self);
  *index = tree->context.index;
  return ts_node_make(
    tree->context.parent,
    ts_node__offset_byte(self) - tree->context.offset.bytes,
    ts_node__offset_row(self) - tree->context.offset.extent.row
  );
}

static inline TSNode ts_node__direct_child(TSNode self, uint32_t i) {
  const Tree *child_tree = ts_node__tree(self)->children[i];
  return ts_node_make(
    child_tree,
    ts_node__offset_byte(self) + child_tree->context.offset.bytes,
    ts_node__offset_row(self) + child_tree->context.offset.extent.row
  );
}

static inline TSNode ts_node__child(TSNode self, uint32_t child_index,
                                    bool include_anonymous) {
  TSNode result = self;
  bool did_descend = true;

  while (did_descend) {
    did_descend = false;

    uint32_t index = 0;
    for (uint32_t i = 0; i < ts_node__tree(result)->child_count; i++) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous)) {
        if (index == child_index)
          return child;
        index++;
      } else {
        uint32_t grandchild_index = child_index - index;
        uint32_t grandchild_count =
          ts_node__relevant_child_count(child, include_anonymous);
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
  TSNode result = self;

  do {
    uint32_t index;
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      break;

    for (uint32_t i = index - 1; i + 1 > 0; i--) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous))
        return child;
      uint32_t grandchild_count =
        ts_node__relevant_child_count(child, include_anonymous);
      if (grandchild_count > 0)
        return ts_node__child(child, grandchild_count - 1, include_anonymous);
    }
  } while (!ts_node__tree(result)->visible);

  return ts_node__null();
}

static inline TSNode ts_node__next_sibling(TSNode self, bool include_anonymous) {
  TSNode result = self;

  do {
    uint32_t index;
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      break;

    for (uint32_t i = index + 1; i < ts_node__tree(result)->child_count; i++) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous))
        return child;
      uint32_t grandchild_count =
        ts_node__relevant_child_count(child, include_anonymous);
      if (grandchild_count > 0)
        return ts_node__child(child, 0, include_anonymous);
    }
  } while (!ts_node__tree(result)->visible);

  return ts_node__null();
}

static inline bool point_gt(TSPoint a, TSPoint b) {
  return a.row > b.row || (a.row == b.row && a.column > b.column);
}

static inline TSNode ts_node__first_child_for_byte(TSNode self, uint32_t goal,
                                                   bool include_anonymous) {
  TSNode node = self;
  bool did_descend = true;

  while (did_descend) {
    did_descend = false;

    for (uint32_t i = 0; i < ts_node__tree(node)->child_count; i++) {
      TSNode child = ts_node__direct_child(node, i);
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

    for (uint32_t i = 0, n = ts_node__tree(node)->child_count; i < n; i++) {
      TSNode child = ts_node__direct_child(node, i);
      if (ts_node_end_byte(child) > max) {
        if (ts_node_start_byte(child) > min) break;
        node = child;
        if (ts_node__is_relevant(node, include_anonymous)) last_visible_node = node;
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
  TSPoint start_position = ts_node_start_point(self);
  TSPoint end_position = ts_node_end_point(self);

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    for (uint32_t i = 0, n = ts_node__tree(node)->child_count; i < n; i++) {
      TSNode child = ts_node__direct_child(node, i);
      const Tree *child_tree = ts_node__tree(child);
      if (i > 0) start_position = point_add(start_position, child_tree->padding.extent);
      end_position = point_add(start_position, child_tree->size.extent);
      if (point_gt(end_position, max)) {
        if (point_gt(start_position, min)) break;
        node = child;
        if (ts_node__is_relevant(node, include_anonymous)) last_visible_node = node;
        did_descend = true;
        break;
      }
      start_position = end_position;
    }
  }

  return last_visible_node;
}

/*
 *  Public
 */

uint32_t ts_node_start_byte(TSNode self) {
  return ts_node__offset_byte(self) + ts_node__tree(self)->padding.bytes;
}

uint32_t ts_node_end_byte(TSNode self) {
  return ts_node_start_byte(self) + ts_node__tree(self)->size.bytes;
}

TSPoint ts_node_start_point(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return (TSPoint){ ts_node__offset_row(self) + tree->padding.extent.row,
                    ts_tree_start_column(tree) };
}

TSPoint ts_node_end_point(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return (TSPoint){ ts_node__offset_row(self) + tree->padding.extent.row +
                      tree->size.extent.row,
                    ts_tree_end_column(tree) };
}

TSSymbol ts_node_symbol(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return tree->context.alias_symbol ? tree->context.alias_symbol : tree->symbol;
}

TSSymbolIterator ts_node_symbols(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return (TSSymbolIterator){
    .value = tree->symbol, .done = false, .data = (void *)tree,
  };
}

void ts_symbol_iterator_next(TSSymbolIterator *self) {
  const Tree *tree = (const Tree *)self->data;
  const Tree *parent = tree->context.parent;
  if (!self->done && parent) {
    if (parent->child_count == 1 && !parent->visible) {
      self->value = parent->symbol;
      self->data = (void *)parent;
      return;
    }
  }
  self->done = true;
}

const char *ts_node_type(TSNode self, const TSDocument *document) {
  return ts_language_symbol_name(document->parser.language, ts_node_symbol(self));
}

char *ts_node_string(TSNode self, const TSDocument *document) {
  return ts_tree_string(ts_node__tree(self), document->parser.language, false);
}

bool ts_node_eq(TSNode self, TSNode other) {
  return
    ts_tree_eq(ts_node__tree(self), ts_node__tree(other)) &&
    self.offset[0] == other.offset[0] &&
    self.offset[1] == other.offset[1];
}

bool ts_node_is_named(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return tree->context.alias_symbol ? tree->context.alias_is_named : tree->named;
}

bool ts_node_is_missing(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  return tree->is_missing;
}

bool ts_node_has_changes(TSNode self) {
  return ts_node__tree(self)->has_changes;
}

bool ts_node_has_error(TSNode self) {
  return ts_node__tree(self)->error_cost > 0;
}

TSNode ts_node_parent(TSNode self) {
  TSNode result = self;
  uint32_t index;

  do {
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      return ts_node__null();
  } while (!ts_node__tree(result)->visible);

  return result;
}

uint32_t ts_node_child_index(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  uint32_t result = 0;

  for (;;) {
    const Tree *parent = tree->context.parent;
    uint32_t index = tree->context.index;
    if (!parent) return UINT32_MAX;
    for (uint32_t i = 0; i < index; i++) {
      Tree *child = parent->children[i];
      result += child->visible ? 1 : child->visible_child_count;
    }
    if (parent->visible) break;
    tree = parent;
  }

  return result;
}

TSNode ts_node_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, true);
}

TSNode ts_node_named_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, false);
}

uint32_t ts_node_child_count(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  if (tree->child_count > 0) {
    return tree->visible_child_count;
  } else {
    return 0;
  }
}

uint32_t ts_node_named_child_count(TSNode self) {
  const Tree *tree = ts_node__tree(self);
  if (tree->child_count > 0) {
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
