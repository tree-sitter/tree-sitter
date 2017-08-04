#include "runtime/get_changed_ranges.h"
#include "runtime/tree.h"
#include "runtime/language.h"
#include "runtime/error_costs.h"

#include <assert.h>

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

static bool tree_is_visible(
  const Tree *tree,
  const Tree *parent,
  uint32_t child_index,
  const TSLanguage *language
) {
  if (tree->visible) return true;

  // if (parent) {
  //   const TSSymbol *alias_sequence = ts_language_alias_sequence(language, parent->alias_sequence_id);
  //   return alias_sequence && alias_sequence[child_index] != 0;
  // }

  return false;
}

static void tree_path_ascend(TreePath *path, uint32_t count, const TSLanguage *language) {
  for (uint32_t i = 0; i < count; i++) {
    while (path->size > 0) {
      path->size--;
      if (path->size == 0) return;
      TreePathEntry *entry = array_back(path);
      Tree *parent = path->size > 1 ? path->contents[path->size - 2].tree : NULL;
      if (tree_is_visible(entry->tree, parent, entry->child_index, language)) break;
    }
  }
}

static bool tree_path_descend(TreePath *path, Length position, const TSLanguage *language) {
  uint32_t original_size = path->size;

  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(path);
    Length child_left = entry.position;
    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < entry.tree->child_count; i++) {
      Tree *child = entry.tree->children[i];
      Length child_right = length_add(child_left, ts_tree_total_size(child));
      if (position.bytes < child_right.bytes) {
        TreePathEntry child_entry = {
          .tree = child,
          .position = child_left,
          .child_index = i,
          .structural_child_index = structural_child_index,
        };
        if (tree_is_visible(child, entry.tree, structural_child_index, language) || child->child_count == 0) {
          array_push(path, child_entry);
          return true;
        }
        if (child->visible_child_count > 0) {
          array_push(path, child_entry);
          did_descend = true;
          break;
        }
      }
      child_left = child_right;
      if (!child->extra) structural_child_index++;
    }
  } while (did_descend);

  path->size = original_size;
  return false;
}

static uint32_t tree_path_advance(TreePath *path, const TSLanguage *language) {
  uint32_t ascend_count = 0;

  while (path->size > 0) {
    TreePathEntry entry = array_pop(path);
    if (path->size == 0) break;
    TreePathEntry parent_entry = *array_back(path);
    if (parent_entry.tree->visible) ascend_count++;

    Length position = length_add(entry.position, ts_tree_total_size(entry.tree));
    uint32_t structural_child_index = entry.structural_child_index;
    if (!entry.tree->extra) structural_child_index++;

    for (uint32_t i = entry.child_index + 1; i < parent_entry.tree->child_count; i++) {
      Tree *next_child = parent_entry.tree->children[i];
      bool is_visible = tree_is_visible(next_child, entry.tree, structural_child_index, language);
      if (is_visible ||
          next_child->child_count == 0 ||
          next_child->visible_child_count > 0) {
        if (parent_entry.tree->visible) ascend_count--;
        array_push(path, ((TreePathEntry){
          .tree = next_child,
          .position = position,
          .child_index = i,
          .structural_child_index = structural_child_index,
        }));
        if (!is_visible) {
          tree_path_descend(path, length_zero(), language);
        }
        return ascend_count;
      }
      position = length_add(position, ts_tree_total_size(next_child));
      if (!next_child->extra) structural_child_index++;
    }
  }

  return ascend_count;
}

static void tree_path_init(TreePath *path, Tree *tree, const TSLanguage *language) {
  array_clear(path);
  array_push(path, ((TreePathEntry){
    .tree = tree,
    .position = { 0, 0, { 0, 0 } },
    .child_index = 0,
    .structural_child_index = 0,
  }));
  if (!tree->visible) tree_path_descend(path, length_zero(), language);
}

Length tree_path_start_position(TreePath *self) {
  TreePathEntry entry = *array_back(self);
  return length_add(entry.position, entry.tree->padding);
}

Length tree_path_end_position(TreePath *self) {
  TreePathEntry entry = *array_back(self);
  return length_add(length_add(entry.position, entry.tree->padding), entry.tree->size);
}

typedef enum {
  TreePathNotEq,
  TreePathCanEq,
  TreePathMustEq,
} TreePathComparison;

TreePathComparison tree_path_compare(const TreePath *old_path,
                                     const TreePath *new_path,
                                     const TSLanguage *language) {
  Tree *old_tree = NULL;
  TSSymbol old_alias_symbol = 0;
  Length old_start = length_zero();
  for (uint32_t i = old_path->size - 1; i + 1 > 0; i--) {
    old_tree = old_path->contents[i].tree;
    old_start = old_path->contents[i].position;
    if (i > 0) {
      Tree *parent = old_path->contents[i - 1].tree;
      const TSSymbol *alias_sequence = ts_language_alias_sequence(language, parent->alias_sequence_id);
      if (alias_sequence) {
        old_alias_symbol = alias_sequence[old_path->contents[i].structural_child_index];
      }
    }

    if (old_tree->visible || old_alias_symbol) break;
  }

  Tree *new_tree = NULL;
  TSSymbol new_alias_symbol = 0;
  Length new_start = length_zero();
  for (uint32_t i = new_path->size - 1; i + 1 > 0; i--) {
    new_tree = new_path->contents[i].tree;
    new_start = old_path->contents[i].position;
    if (i > 0) {
      Tree *parent = new_path->contents[i - 1].tree;
      const TSSymbol *alias_sequence = ts_language_alias_sequence(language, parent->alias_sequence_id);
      if (alias_sequence) {
        new_alias_symbol = alias_sequence[new_path->contents[i].structural_child_index];
      }
    }

    if (new_tree->visible || new_alias_symbol) break;
  }

  if (old_alias_symbol == new_alias_symbol) {
    if (old_start.bytes == new_start.bytes) {
      if (!old_tree->has_changes &&
          old_tree->symbol == new_tree->symbol &&
          old_tree->symbol != ts_builtin_sym_error &&
          old_tree->size.bytes == new_tree->size.bytes &&
          old_tree->parse_state != TS_TREE_STATE_NONE &&
          new_tree->parse_state != TS_TREE_STATE_NONE &&
          (old_tree->parse_state == ERROR_STATE) == (new_tree->parse_state == ERROR_STATE)) {
        return TreePathMustEq;
      }
    }

    if (old_tree->symbol == new_tree->symbol) {
      return TreePathCanEq;
    }
  }

  return TreePathNotEq;
}

unsigned ts_tree_get_changed_ranges(
  Tree *old_tree, Tree *new_tree,
  TreePath *old_path, TreePath *new_path,
  const TSLanguage *language, TSRange **ranges
) {
  tree_path_init(old_path, old_tree, language);
  tree_path_init(new_path, new_tree, language);
  Length position = length_zero();
  RangeArray results = array_new();

  while (old_path->size && new_path->size) {
    bool is_changed = false;
    Length next_position = position;

    Length old_start = tree_path_start_position(old_path);
    Length new_start = tree_path_start_position(new_path);
    Length old_end = tree_path_end_position(old_path);
    Length new_end = tree_path_end_position(new_path);

    // #define NAME(tree) (ts_language_symbol_name(language, ((Tree *)(tree))->symbol))
    // printf("At [%-2u, %-2u] Compare (%-20s\t [%u, %u] - [%u, %u])\tvs\t(%-20s\t [%u, %u] - [%u, %u])\t",
    //   position.extent.row, position.extent.column,
    //   NAME(array_back(old_path)->tree), old_start.extent.row, old_start.extent.column, old_end.extent.row, old_end.extent.column,
    //   NAME(array_back(old_path)->tree), new_start.extent.row, new_start.extent.column, new_end.extent.row, new_end.extent.column);

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
    } else {
      switch (tree_path_compare(old_path, new_path, language)) {
        case TreePathMustEq:
          next_position = old_end;
          break;

        case TreePathCanEq:
          if (tree_path_descend(old_path, position, language)) {
            if (!tree_path_descend(new_path, position, language)) {
              tree_path_ascend(old_path, 1, language);
              is_changed = true;
              next_position = new_end;
            }
          } else if (tree_path_descend(new_path, position, language)) {
            tree_path_ascend(new_path, 1, language);
            is_changed = true;
            next_position = old_end;
          } else {
            next_position = length_min(old_end, new_end);
          }
          break;

        case TreePathNotEq:
          is_changed = true;
          next_position = length_min(old_end, new_end);
          break;
      }
    }

    bool at_old_end = old_end.bytes <= next_position.bytes;
    bool at_new_end = new_end.bytes <= next_position.bytes;

    if (at_new_end && at_old_end) {
      uint32_t old_ascend_count = tree_path_advance(old_path, language);
      uint32_t new_ascend_count = tree_path_advance(new_path, language);
      if (old_ascend_count > new_ascend_count) {
        tree_path_ascend(new_path, old_ascend_count - new_ascend_count, language);
      } else if (new_ascend_count > old_ascend_count) {
        tree_path_ascend(old_path, new_ascend_count - old_ascend_count, language);
      }
    } else if (at_new_end) {
      uint32_t ascend_count = tree_path_advance(new_path, language);
      tree_path_ascend(old_path, ascend_count, language);
    } else if (at_old_end) {
      uint32_t ascend_count = tree_path_advance(old_path, language);
      tree_path_ascend(new_path, ascend_count, language);
    }

    if (is_changed) {
      range_array_add(&results, position.extent, next_position.extent);
    }
    position = next_position;
  }

  *ranges = results.contents;
  return results.size;
}
