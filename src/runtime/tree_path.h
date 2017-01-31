#ifndef RUNTIME_TREE_PATH_H_
#define RUNTIME_TREE_PATH_H_

#include "runtime/tree.h"
#include "runtime/error_costs.h"

typedef Array(TSRange) RangeArray;

static void range_array_add(RangeArray *results, TSPoint start, TSPoint end) {
  if (results->size > 0) {
    TSRange *last_range = array_back(results);
    if (point_lte(start, last_range->end)) {
      last_range->end = end;
      return;
    }
  }

  if (point_lt(start, end)) {
    TSRange range = { start, end };
    array_push(results, range);
  }
}

static bool tree_path_descend(TreePath *path, Length position) {
  uint32_t original_size = path->size;

  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(path);
    Length child_left = entry.position;
    for (uint32_t i = 0; i < entry.tree->child_count; i++) {
      Tree *child = entry.tree->children[i];
      Length child_right = length_add(child_left, ts_tree_total_size(child));
      if (position.bytes < child_right.bytes) {
        TreePathEntry child_entry = { child, child_left, i };
        if (child->visible || child->child_count == 0) {
          array_push(path, child_entry);
          return true;
        } else if (child->visible_child_count > 0) {
          array_push(path, child_entry);
          did_descend = true;
          break;
        }
      }
      child_left = child_right;
    }
  } while (did_descend);

  path->size = original_size;
  return false;
}

static uint32_t tree_path_advance(TreePath *path) {
  uint32_t ascend_count = 0;

  while (path->size > 0) {
    TreePathEntry entry = array_pop(path);
    if (path->size == 0) break;
    TreePathEntry parent_entry = *array_back(path);
    if (parent_entry.tree->visible) ascend_count++;

    Length position = length_add(entry.position, ts_tree_total_size(entry.tree));
    for (uint32_t i = entry.child_index + 1; i < parent_entry.tree->child_count; i++) {
      Tree *next_child = parent_entry.tree->children[i];
      if (next_child->visible ||
          next_child->child_count == 0 ||
          next_child->visible_child_count > 0) {
        if (parent_entry.tree->visible) ascend_count--;
        array_push(path, ((TreePathEntry){
          .tree = next_child,
          .child_index = i,
          .position = position,
        }));
        if (!next_child->visible) {
          tree_path_descend(path, length_zero());
        }
        return ascend_count;
      }
      position = length_add(position, ts_tree_total_size(next_child));
    }
  }

  return ascend_count;
}

static void tree_path_ascend(TreePath *path, uint32_t count) {
  for (uint32_t i = 0; i < count; i++) {
    do {
      path->size--;
    } while (path->size > 0 && !array_back(path)->tree->visible);
  }
}

static void tree_path_init(TreePath *path, Tree *tree) {
  array_clear(path);
  array_push(path, ((TreePathEntry){
    .tree = tree,
    .position = { 0, 0, { 0, 0 } },
    .child_index = 0,
  }));
  if (!tree->visible) {
    tree_path_descend(path, length_zero());
  }
}

Tree *tree_path_visible_tree(TreePath *self) {
  for (uint32_t i = self->size - 1; i + 1 > 0; i--) {
    Tree *tree = self->contents[i].tree;
    if (tree->visible) return tree;
  }
  return NULL;
}

Length tree_path_start_position(TreePath *self) {
  TreePathEntry entry = *array_back(self);
  return length_add(entry.position, entry.tree->padding);
}

Length tree_path_end_position(TreePath *self) {
  TreePathEntry entry = *array_back(self);
  return length_add(length_add(entry.position, entry.tree->padding), entry.tree->size);
}

static bool tree_must_eq(Tree *old_tree, Tree *new_tree) {
  return old_tree == new_tree || (
    !old_tree->has_changes &&
    old_tree->symbol == new_tree->symbol &&
    old_tree->size.bytes == new_tree->size.bytes &&
    old_tree->parse_state != TS_TREE_STATE_NONE &&
    new_tree->parse_state != TS_TREE_STATE_NONE &&
    (old_tree->parse_state == ERROR_STATE) ==
    (new_tree->parse_state == ERROR_STATE)
  );
}

static void tree_path_get_changes(TreePath *old_path, TreePath *new_path,
                                  TSRange **ranges, uint32_t *range_count) {
  Length position = length_zero();
  RangeArray results = array_new();

  while (old_path->size && new_path->size) {
    bool is_changed = false;
    Length next_position = position;

    Tree *old_tree = tree_path_visible_tree(old_path);
    Tree *new_tree = tree_path_visible_tree(new_path);
    Length old_start = tree_path_start_position(old_path);
    Length new_start = tree_path_start_position(new_path);
    Length old_end = tree_path_end_position(old_path);
    Length new_end = tree_path_end_position(new_path);

    // #define NAME(t) (ts_language_symbol_name(language, ((Tree *)(t))->symbol))
    // printf("At [%-2u, %-2u] Compare (%-20s\t [%-2u, %-2u] - [%u, %u])\tvs\t(%-20s\t [%u, %u] - [%u, %u])\n",
    //   position.extent.row, position.extent.column,
    //   NAME(old_tree), old_start.extent.row, old_start.extent.column, old_end.extent.row, old_end.extent.column,
    //   NAME(new_tree), new_start.extent.row, new_start.extent.column, new_end.extent.row, new_end.extent.column);

    if (position.bytes < old_start.bytes) {
      if (position.bytes < new_start.bytes) {
        next_position = length_min(old_start, new_start);
      } else {
        is_changed = true;
        next_position = old_start;
      }
    } else if (position.bytes < new_start.bytes) {
      is_changed = true;
      next_position = new_start;
    } else if (old_start.bytes == new_start.bytes && tree_must_eq(old_tree, new_tree)) {
      next_position = old_end;
    } else if (old_tree->symbol == new_tree->symbol) {
      if (tree_path_descend(old_path, position)) {
        if (!tree_path_descend(new_path, position)) {
          tree_path_ascend(old_path, 1);
          is_changed = true;
          next_position = new_end;
        }
      } else if (tree_path_descend(new_path, position)) {
        tree_path_ascend(new_path, 1);
        is_changed = true;
        next_position = old_end;
      } else {
        next_position = length_min(old_end, new_end);
      }
    } else {
      is_changed = true;
      next_position = length_min(old_end, new_end);
    }

    bool at_old_end = old_end.bytes <= next_position.bytes;
    bool at_new_end = new_end.bytes <= next_position.bytes;

    if (at_new_end && at_old_end) {
      uint32_t old_ascend_count = tree_path_advance(old_path);
      uint32_t new_ascend_count = tree_path_advance(new_path);
      if (old_ascend_count > new_ascend_count) {
        tree_path_ascend(new_path, old_ascend_count - new_ascend_count);
      } else if (new_ascend_count > old_ascend_count) {
        tree_path_ascend(old_path, new_ascend_count - old_ascend_count);
      }
    } else if (at_new_end) {
      uint32_t ascend_count = tree_path_advance(new_path);
      tree_path_ascend(old_path, ascend_count);
    } else if (at_old_end) {
      uint32_t ascend_count = tree_path_advance(old_path);
      tree_path_ascend(new_path, ascend_count);
    }

    if (is_changed) range_array_add(&results, position.extent, next_position.extent);
    position = next_position;
  }

  *ranges = results.contents;
  *range_count = results.size;
}

#endif  // RUNTIME_TREE_PATH_H_
