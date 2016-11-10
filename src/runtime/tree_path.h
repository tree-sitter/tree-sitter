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

static bool tree_path_descend(TreePath *path, TSPoint position) {
  size_t original_size = path->size;
  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(path);
    Length child_position = entry.position;
    for (size_t i = 0; i < entry.tree->child_count; i++) {
      Tree *child = entry.tree->children[i];
      Length child_right_position =
        length_add(child_position, ts_tree_total_size(child));
      if (point_lt(position, child_right_position.extent)) {
        TreePathEntry child_entry = { child, child_position, i };
        if (child->visible) {
          array_push(path, child_entry);
          return true;
        } else if (child->visible_child_count > 0) {
          array_push(path, child_entry);
          did_descend = true;
          break;
        }
      }
      child_position = child_right_position;
    }
  } while (did_descend);
  path->size = original_size;
  return false;
}

static size_t tree_path_advance(TreePath *path) {
  size_t ascend_count = 0;
  while (path->size > 0) {
    TreePathEntry entry = array_pop(path);
    if (path->size == 0)
      break;
    TreePathEntry parent_entry = *array_back(path);
    if (parent_entry.tree->visible) ascend_count++;
    Length position =
      length_add(entry.position, ts_tree_total_size(entry.tree));
    for (size_t i = entry.child_index + 1; i < parent_entry.tree->child_count; i++) {
      Tree *next_child = parent_entry.tree->children[i];
      if (next_child->visible || next_child->visible_child_count > 0) {
        if (parent_entry.tree->visible) ascend_count--;
        array_push(path, ((TreePathEntry){
          .tree = next_child,
          .child_index = i,
          .position = position,
        }));
        if (!next_child->visible)
          tree_path_descend(path, (TSPoint){ 0, 0 });
        return ascend_count;
      }
      position = length_add(position, ts_tree_total_size(next_child));
    }
  }
  return ascend_count;
}

static void tree_path_ascend(TreePath *path, size_t count) {
  for (size_t i = 0; i < count; i++) {
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
  if (!tree->visible)
    tree_path_descend(path, (TSPoint){ 0, 0 });
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
                                  TSRange **ranges, size_t *range_count) {
  TSPoint position = { 0, 0 };
  RangeArray results = array_new();

  while (old_path->size && new_path->size) {
    bool is_changed = false;
    TSPoint next_position = position;

    TreePathEntry old_entry = *array_back(old_path);
    TreePathEntry new_entry = *array_back(new_path);
    Tree *old_tree = old_entry.tree;
    Tree *new_tree = new_entry.tree;
    size_t old_start_byte = old_entry.position.bytes + old_tree->padding.bytes;
    size_t new_start_byte = new_entry.position.bytes + new_tree->padding.bytes;
    TSPoint old_start_point =
      point_add(old_entry.position.extent, old_tree->padding.extent);
    TSPoint new_start_point =
      point_add(new_entry.position.extent, new_tree->padding.extent);
    TSPoint old_end_point = point_add(old_start_point, old_tree->size.extent);
    TSPoint new_end_point = point_add(new_start_point, new_tree->size.extent);

    // #define NAME(t) (ts_language_symbol_name(language, ((Tree *)(t))->symbol))
    // printf("At [%-2lu, %-2lu] Compare (%-20s\t [%-2lu, %-2lu] - [%lu, %lu])\tvs\t(%-20s\t [%lu, %lu] - [%lu, %lu])\n",
    //   position.row, position.column, NAME(old_tree), old_start_point.row,
    //   old_start_point.column, old_end_point.row, old_end_point.column,
    //   NAME(new_tree), new_start_point.row, new_start_point.column,
    //   new_end_point.row, new_end_point.column);

    if (point_lt(position, old_start_point)) {
      if (point_lt(position, new_start_point)) {
        next_position = point_min(old_start_point, new_start_point);
      } else {
        is_changed = true;
        next_position = old_start_point;
      }
    } else if (point_lt(position, new_start_point)) {
      is_changed = true;
      next_position = new_start_point;
    } else if (old_start_byte == new_start_byte &&
               tree_must_eq(old_tree, new_tree)) {
      next_position = old_end_point;
    } else if (old_tree->symbol == new_tree->symbol) {
      if (tree_path_descend(old_path, position)) {
        if (!tree_path_descend(new_path, position)) {
          tree_path_ascend(old_path, 1);
          is_changed = true;
          next_position = new_end_point;
        }
      } else if (tree_path_descend(new_path, position)) {
        tree_path_ascend(new_path, 1);
        is_changed = true;
        next_position = old_end_point;
      } else {
        next_position = point_min(old_end_point, new_end_point);
      }
    } else {
      is_changed = true;
      next_position = point_min(old_end_point, new_end_point);
    }

    bool at_old_end = point_lte(old_end_point, next_position);
    bool at_new_end = point_lte(new_end_point, next_position);

    if (at_new_end && at_old_end) {
      size_t old_ascend_count = tree_path_advance(old_path);
      size_t new_ascend_count = tree_path_advance(new_path);
      if (old_ascend_count > new_ascend_count) {
        tree_path_ascend(new_path, old_ascend_count - new_ascend_count);
      } else if (new_ascend_count > old_ascend_count) {
        tree_path_ascend(old_path, new_ascend_count - old_ascend_count);
      }
    } else if (at_new_end) {
      size_t ascend_count = tree_path_advance(new_path);
      tree_path_ascend(old_path, ascend_count);
    } else if (at_old_end) {
      size_t ascend_count = tree_path_advance(old_path);
      tree_path_ascend(new_path, ascend_count);
    }

    if (is_changed) range_array_add(&results, position, next_position);
    position = next_position;
  }

  *ranges = results.contents;
  *range_count = results.size;
}

#endif  // RUNTIME_TREE_PATH_H_
