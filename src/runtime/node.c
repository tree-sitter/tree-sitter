#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const TSTree *tree, size_t chars, size_t byte, size_t row) {
  return (TSNode){.data = tree, .offset = { chars, byte, row } };
}

/*
 *  Private
 */

static inline TSNode ts_node__null() {
  return ts_node_make(NULL, 0, 0, 0);
}

static inline const TSTree *ts_node__tree(TSNode self) {
  return self.data;
}

static inline size_t ts_node__offset_char(TSNode self) {
  return self.offset[0];
}

static inline size_t ts_node__offset_byte(TSNode self) {
  return self.offset[1];
}

static inline size_t ts_node__offset_row(TSNode self) {
  return self.offset[2];
}

static inline bool ts_node__is_relevant(TSNode self, bool include_anonymous) {
  const TSTree *tree = ts_node__tree(self);
  return include_anonymous ? tree->visible : tree->named;
}

static inline size_t ts_node__relevant_child_count(TSNode self,
                                                   bool include_anonymous) {
  const TSTree *tree = ts_node__tree(self);
  return include_anonymous ? tree->visible_child_count : tree->named_child_count;
}

static inline TSNode ts_node__direct_parent(TSNode self, size_t *index) {
  const TSTree *tree = ts_node__tree(self);
  *index = tree->context.index;
  return ts_node_make(tree->context.parent,
                      ts_node__offset_char(self) - tree->context.offset.chars,
                      ts_node__offset_byte(self) - tree->context.offset.bytes,
                      ts_node__offset_row(self) - tree->context.offset.rows);
}

static inline TSNode ts_node__direct_child(TSNode self, size_t i) {
  const TSTree *child_tree = ts_node__tree(self)->children[i];
  return ts_node_make(
    child_tree, ts_node__offset_char(self) + child_tree->context.offset.chars,
    ts_node__offset_byte(self) + child_tree->context.offset.bytes,
    ts_node__offset_row(self) + child_tree->context.offset.rows);
}

static inline TSNode ts_node__child(TSNode self, size_t child_index,
                                    bool include_anonymous) {
  TSNode result = self;
  bool did_descend = true;

  while (did_descend) {
    did_descend = false;

    size_t index = 0;
    for (size_t i = 0; i < ts_node__tree(result)->child_count; i++) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous)) {
        if (index == child_index)
          return child;
        index++;
      } else {
        size_t grandchild_index = child_index - index;
        size_t grandchild_count =
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
    size_t index;
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      break;

    for (size_t i = index - 1; i + 1 > 0; i--) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous))
        return child;
      size_t grandchild_count =
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
    size_t index;
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      break;

    for (size_t i = index + 1; i < ts_node__tree(result)->child_count; i++) {
      TSNode child = ts_node__direct_child(result, i);
      if (ts_node__is_relevant(child, include_anonymous))
        return child;
      size_t grandchild_count =
        ts_node__relevant_child_count(child, include_anonymous);
      if (grandchild_count > 0)
        return ts_node__child(child, 0, include_anonymous);
    }
  } while (!ts_node__tree(result)->visible);

  return ts_node__null();
}

static inline TSNode ts_node__descendant_for_range(TSNode self, size_t min,
                                                   size_t max,
                                                   bool include_anonymous) {
  TSNode node = self;
  TSNode last_visible_node = self;

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    for (size_t i = 0; i < ts_node__tree(node)->child_count; i++) {
      TSNode child = ts_node__direct_child(node, i);
      if (ts_node_start_char(child) > min)
        break;
      if (ts_node_end_char(child) > max) {
        node = child;
        if (ts_node__is_relevant(node, include_anonymous))
          last_visible_node = node;
        did_descend = true;
        break;
      }
    }
  }

  return last_visible_node;
}

/*
 *  Public
 */

size_t ts_node_start_char(TSNode self) {
  return ts_node__offset_char(self) + ts_node__tree(self)->padding.chars;
}

size_t ts_node_end_char(TSNode self) {
  return ts_node_start_char(self) + ts_node__tree(self)->size.chars;
}

size_t ts_node_start_byte(TSNode self) {
  return ts_node__offset_byte(self) + ts_node__tree(self)->padding.bytes;
}

size_t ts_node_end_byte(TSNode self) {
  return ts_node_start_byte(self) + ts_node__tree(self)->size.bytes;
}

TSPoint ts_node_start_point(TSNode self) {
  const TSTree *tree = ts_node__tree(self);
  return (TSPoint){ ts_node__offset_row(self) + tree->padding.rows,
                    ts_tree_start_column(tree) };
}

TSPoint ts_node_end_point(TSNode self) {
  const TSTree *tree = ts_node__tree(self);
  return (TSPoint){ ts_node__offset_row(self) + tree->padding.rows +
                      tree->size.rows,
                    ts_tree_end_column(tree) };
}

TSSymbol ts_node_symbol(TSNode self) {
  return ts_node__tree(self)->symbol;
}

const char *ts_node_name(TSNode self, const TSDocument *document) {
  return document->parser.language->symbol_names[ts_node__tree(self)->symbol];
}

const char *ts_node_string(TSNode self, const TSDocument *document) {
  return ts_tree_string(ts_node__tree(self),
                        document->parser.language->symbol_names, false);
}

bool ts_node_eq(TSNode self, TSNode other) {
  return ts_tree_eq(ts_node__tree(self), ts_node__tree(other)) &&
         self.offset[0] == other.offset[0] &&
         self.offset[1] == other.offset[1] && self.offset[2] == other.offset[2];
}

bool ts_node_is_named(TSNode self) {
  return ts_node__tree(self)->named;
}

bool ts_node_has_changes(TSNode self) {
  return ts_node__tree(self)->has_changes;
}

TSNode ts_node_parent(TSNode self) {
  TSNode result = self;
  size_t index;

  do {
    result = ts_node__direct_parent(result, &index);
    if (!result.data)
      return ts_node__null();
  } while (!ts_node__tree(result)->visible);

  return result;
}

TSNode ts_node_child(TSNode self, size_t child_index) {
  return ts_node__child(self, child_index, true);
}

TSNode ts_node_named_child(TSNode self, size_t child_index) {
  return ts_node__child(self, child_index, false);
}

size_t ts_node_child_count(TSNode self) {
  return ts_node__tree(self)->visible_child_count;
}

size_t ts_node_named_child_count(TSNode self) {
  return ts_node__tree(self)->named_child_count;
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

TSNode ts_node_descendant_for_range(TSNode self, size_t min, size_t max) {
  return ts_node__descendant_for_range(self, min, max, true);
}

TSNode ts_node_named_descendant_for_range(TSNode self, size_t min, size_t max) {
  return ts_node__descendant_for_range(self, min, max, false);
}
