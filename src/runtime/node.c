#include <stdbool.h>
#include "runtime/node.h"
#include "runtime/length.h"
#include "runtime/tree.h"
#include "runtime/document.h"

TSNode ts_node_make(const TSTree *tree, TSLength offset, TSPoint point) {
  return (TSNode){.data = tree, .offset = offset, .point = point };
}

/*
 *  Private
 */

static inline TSNode ts_node__null() {
  return ts_node_make(NULL, ts_length_zero(), ts_point_zero());
}

static inline const TSTree *ts_node__tree(TSNode self) {
  return self.data;
}

static inline TSLength ts_node__offset(TSNode self) {
  return self.offset;
}


static inline TSPoint ts_node__point(TSNode self) {
  return self.point;
}

static inline TSNode ts_node__child(TSNode self, size_t child_index,
                                    TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength position = ts_node__offset(self);
  TSPoint point = ts_node__point(self);

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    size_t index = 0;
    for (size_t i = 0; i < tree->child_count; i++) {
      TSTree *child = tree->children[i];
      if (child->options.type >= type) {
        if (index == child_index)
          return ts_node_make(child, position, point);
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
    }
  }

  return ts_node__null();
}

static inline TSNode ts_node__prev_sibling(TSNode self, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength position = ts_node__offset(self);
  TSPoint point = ts_node__point(self);

  do {
    size_t index = tree->context.index;
    position = ts_length_sub(position, tree->context.offset);
    point = ts_point_sub(point, tree->context.offset_point);
    tree = tree->context.parent;
    if (!tree)
      break;

    for (size_t i = index - 1; i + 1 > 0; i--) {
      const TSTree *child = tree->children[i];
      TSLength child_position = ts_length_add(position, child->context.offset);
      TSPoint child_point = ts_point_add(point, child->context.offset_point);
      if (child->options.type >= type)
        return ts_node_make(child, child_position, child_point);
      size_t grandchild_count = (type == TSNodeTypeNamed)
                                  ? child->named_child_count
                                  : child->visible_child_count;
      if (grandchild_count > 0)
        return ts_node__child(ts_node_make(child, child_position, child_point),
                              grandchild_count - 1, type);
    }
  } while (!ts_tree_is_visible(tree));

  return ts_node__null();
}

static inline TSNode ts_node__next_sibling(TSNode self, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self);
  TSLength position = ts_node__offset(self);
  TSPoint point = ts_node__point(self);

  do {
    size_t index = tree->context.index;
    position = ts_length_sub(position, tree->context.offset);
    tree = tree->context.parent;
    if (!tree)
      break;

    for (size_t i = index + 1; i < tree->child_count; i++) {
      const TSTree *child = tree->children[i];
      TSLength child_position = ts_length_add(position, child->context.offset);
      TSPoint child_point = ts_point_add(point, child->context.offset_point);
      if (child->options.type >= type)
        return ts_node_make(child, child_position, child_point);
      size_t grandchild_count = (type == TSNodeTypeNamed)
                                  ? child->named_child_count
                                  : child->visible_child_count;
      if (grandchild_count > 0)
        return ts_node__child(ts_node_make(child, child_position, child_point), 0, type);
    }
  } while (!ts_tree_is_visible(tree));

  return ts_node__null();
}

static inline TSNode ts_node__descendent_for_range(TSNode self, size_t min,
                                                   size_t max, TSNodeType type) {
  const TSTree *tree = ts_node__tree(self), *last_visible_tree = tree;
  TSLength position = ts_node__offset(self), last_visible_position = position;
  TSPoint point = ts_node__point(self), last_visible_point = point;

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
        }
        did_descend = true;
        break;
      }
      position = ts_length_add(position, ts_tree_total_size(child));
    }
  }

  return ts_node_make(last_visible_tree, last_visible_position, last_visible_point);
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

TSPoint ts_node_point(TSNode self) {
  return ts_node__tree(self)->size_point;
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
         ts_length_eq(ts_node__offset(self), ts_node__offset(other));
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
	TSPoint point = ts_node__point(self);

  do {
    position = ts_length_sub(position, tree->context.offset);
		point = ts_point_sub(point, tree->context.offset_point);

    tree = tree->context.parent;
    if (!tree)
      return ts_node__null();
  } while (!ts_tree_is_visible(tree));

  return ts_node_make(tree, position, point);
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
