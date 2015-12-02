#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/length.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const TSTree *tree, TSLength offset, size_t row) {
  return (TSNode){.data = tree, .offset = offset, .row = row };
}

/*
 *  Private
 */

static inline TSNode ts_node__null() {
  return ts_node_make(NULL, ts_length_zero(), 0);
}

static inline const TSTree *ts_node__tree(TSNode self) {
  return self.data;
}

static inline TSLength ts_node__offset(TSNode self) {
  return self.offset;
}


static inline TSNode ts_node__child(TSNode self, size_t child_index,
                                    TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength position = ts_node__offset(self);
  size_t offset_row = self.row;

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    size_t index = 0;
    for (size_t i = 0; i < tree->child_count; i++) {
      TSTree *child = tree->children[i];
      if (child->options.type >= type) {
        if (index == child_index)
          return ts_node_make(child, position, offset_row);
        index++;
      } else {
        size_t grandchild_index = child_index - index;
        size_t grandchild_count = (type == TSNodeTypeNamed)
                                    ? child->named_child_count
                                    : child->visible_child_count;
        if (grandchild_index < grandchild_count) {
          did_descend = true;
          tree = child;
          child_index = grandchild_index;
          break;
        }
        index += grandchild_count;
      }
      position = ts_length_add(position, ts_tree_total_size(child));
      offset_row += child->padding_point.row + child->size_point.row;
    }
  }

  return ts_node__null();
}

static inline TSNode ts_node__prev_sibling(TSNode self, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength offset = ts_node__offset(self);
  size_t offset_row = self.row;

  do {
    size_t index = tree->context.index;
    offset = ts_length_sub(offset, tree->context.offset);
    offset_row -= tree->context.offset_point.row;
    tree = tree->context.parent;
    if (!tree)
      break;

    for (size_t i = index - 1; i + 1 > 0; i--) {
      const TSTree *child = tree->children[i];
      TSLength child_offset = ts_length_add(offset, child->context.offset);
      size_t child_offset_row = offset_row + child->context.offset_point.row;
      if (child->options.type >= type)
        return ts_node_make(child, child_offset, child_offset_row);
      size_t grandchild_count = (type == TSNodeTypeNamed)
                                  ? child->named_child_count
                                  : child->visible_child_count;
      if (grandchild_count > 0)
        return ts_node__child(ts_node_make(child, child_offset, child_offset_row),
                              grandchild_count - 1, type);
    }
  } while (!ts_tree_is_visible(tree));

  return ts_node__null();
}

static inline TSNode ts_node__next_sibling(TSNode self, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength offset = ts_node__offset(self);
  size_t offset_row = self.row;

  do {
    size_t index = tree->context.index;
    offset = ts_length_sub(offset, tree->context.offset);
    offset_row -= tree->context.offset_point.row;
    tree = tree->context.parent;
    if (!tree)
      break;

    for (size_t i = index + 1; i < tree->child_count; i++) {
      const TSTree *child = tree->children[i];
      TSLength child_offset = ts_length_add(offset, child->context.offset);
      size_t child_offset_row = offset_row + child->context.offset_point.row;
      if (child->options.type >= type)
        return ts_node_make(child, child_offset, child_offset_row);
      size_t grandchild_count = (type == TSNodeTypeNamed)
                                  ? child->named_child_count
                                  : child->visible_child_count;
      if (grandchild_count > 0)
        return ts_node__child(ts_node_make(child, child_offset, child_offset_row), 0, type);
    }
  } while (!ts_tree_is_visible(tree));

  return ts_node__null();
}

static inline TSNode ts_node__descendent_for_range(TSNode self, size_t min,
                                                   size_t max, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self), *last_visible_tree = tree;
  TSLength position = ts_node__offset(self), last_visible_position = position;
  size_t offset_row = self.row, last_visible_row = offset_row;

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    for (size_t i = 0; i < tree->child_count; i++) {
      const TSTree *child = tree->children[i];
      if (position.chars + child->padding.chars > min)
        break;
      if (position.chars + child->padding.chars + child->size.chars > max) {
        tree = child;
        if (child->options.type >= type) {
          last_visible_tree = tree;
          last_visible_position = position;
          last_visible_row = offset_row;
        }
        did_descend = true;
        break;
      }
      position = ts_length_add(position, ts_tree_total_size(child));
      offset_row += child->padding_point.row + child->size_point.row;
    }
  }

  return ts_node_make(last_visible_tree, last_visible_position, last_visible_row);
}

/*
 *  Public
 */

TSLength ts_node_pos(TSNode self) {
  return ts_length_add(ts_node__offset(self), ts_node__tree(self)->padding);
}

TSLength ts_node_size(TSNode self) {
  return ts_node__tree(self)->size;
}

TSPoint ts_node_size_point(TSNode self) {
  return ts_node__tree(self)->size_point;
}

TSPoint ts_node_start_point(TSNode self) {
  const TSTree *tree = ts_node__tree(self);
  return ts_point_make(self.row + tree->padding_point.row, ts_tree_offset_column(tree));
}

TSPoint ts_node_end_point(TSNode self) {
  return ts_point_add(ts_node_start_point(self), ts_node_size_point(self));
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
         ts_length_eq(ts_node__offset(self), ts_node__offset(other)) &&
         self.row == other.row;
}

bool ts_node_is_named(TSNode self) {
  return ts_node__tree(self)->options.type == TSNodeTypeNamed;
}

bool ts_node_has_changes(TSNode self) {
  return ts_node__tree(self)->options.has_changes;
}

TSNode ts_node_parent(TSNode self) {
  const TSTree *tree = ts_node__tree(self);
  TSLength position = ts_node__offset(self);
	size_t offset_row = self.row;

  do {
    position = ts_length_sub(position, tree->context.offset);
		offset_row -= tree->context.offset_point.row;

    tree = tree->context.parent;
    if (!tree)
      return ts_node__null();
  } while (!ts_tree_is_visible(tree));

  return ts_node_make(tree, position, offset_row);
}

TSNode ts_node_child(TSNode self, size_t child_index) {
  return ts_node__child(self, child_index, TSNodeTypeAnonymous);
}

TSNode ts_node_named_child(TSNode self, size_t child_index) {
  return ts_node__child(self, child_index, TSNodeTypeNamed);
}

size_t ts_node_child_count(TSNode self) {
  return ts_node__tree(self)->visible_child_count;
}

size_t ts_node_named_child_count(TSNode self) {
  return ts_node__tree(self)->named_child_count;
}

TSNode ts_node_next_sibling(TSNode self) {
  return ts_node__next_sibling(self, TSNodeTypeAnonymous);
}

TSNode ts_node_next_named_sibling(TSNode self) {
  return ts_node__next_sibling(self, TSNodeTypeNamed);
}

TSNode ts_node_prev_sibling(TSNode self) {
  return ts_node__prev_sibling(self, TSNodeTypeAnonymous);
}

TSNode ts_node_prev_named_sibling(TSNode self) {
  return ts_node__prev_sibling(self, TSNodeTypeNamed);
}

TSNode ts_node_descendent_for_range(TSNode self, size_t min, size_t max) {
  return ts_node__descendent_for_range(self, min, max, TSNodeTypeAnonymous);
}

TSNode ts_node_named_descendent_for_range(TSNode self, size_t min, size_t max) {
  return ts_node__descendent_for_range(self, min, max, TSNodeTypeNamed);
}
