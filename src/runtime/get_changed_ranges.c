#include "runtime/get_changed_ranges.h"
#include "runtime/tree.h"
#include "runtime/language.h"
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

typedef struct {
  TreePath path;
  const TSLanguage *language;
  unsigned visible_depth;
  bool in_padding;
} Iterator;

static Iterator iterator_new(TreePath *path, Tree *tree, const TSLanguage *language) {
  array_clear(path);
  array_push(path, ((TreePathEntry){
    .tree = tree,
    .position = length_zero(),
    .child_index = 0,
    .structural_child_index = 0,
  }));
  return (Iterator) {
    .path = *path,
    .language = language,
    .visible_depth = 1,
    .in_padding = false,
  };
}

static bool iterator_done(Iterator *self) {
  return self->path.size == 0;
}

Length iterator_start_position(Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  if (self->in_padding) {
    return entry.position;
  } else {
    return length_add(entry.position, entry.tree->padding);
  }
}

Length iterator_end_position(Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  Length result = length_add(entry.position, entry.tree->padding);
  if (self->in_padding) {
    return result;
  } else {
    return length_add(result, entry.tree->size);
  }
}

static bool iterator_tree_is_visible(const Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  if (entry.tree->visible) return true;
  if (self->path.size > 1) {
    Tree *parent = self->path.contents[self->path.size - 2].tree;
    const TSSymbol *alias_sequence = ts_language_alias_sequence(self->language, parent->alias_sequence_id);
    return alias_sequence && alias_sequence[entry.structural_child_index] != 0;
  }
  return false;
}

static void iterator_get_visible_state(const Iterator *self, Tree **tree,
                                       TSSymbol *alias_symbol, uint32_t *start_byte) {
  uint32_t i = self->path.size - 1;

  if (self->in_padding) {
    while (self->path.contents[i].child_index == 0) i--;
  }

  for (; i + 1 > 0; i--) {
    TreePathEntry entry = self->path.contents[i];

    if (i > 0) {
      Tree *parent = self->path.contents[i - 1].tree;
      const TSSymbol *alias_sequence = ts_language_alias_sequence(
        self->language,
        parent->alias_sequence_id
      );
      if (alias_sequence) {
        *alias_symbol = alias_sequence[entry.structural_child_index];
      }
    }

    if (entry.tree->visible || *alias_symbol) {
      *tree = entry.tree;
      *start_byte = entry.position.bytes;
      break;
    }
  }
}

static void iterator_ascend(Iterator *self) {
  if (iterator_done(self)) return;
  if (iterator_tree_is_visible(self) && !self->in_padding) self->visible_depth--;
  if (array_back(&self->path)->child_index > 0) self->in_padding = false;
  self->path.size--;
}

static bool iterator_descend(Iterator *self, uint32_t goal_position) {
  if (self->in_padding) return false;

  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(&self->path);
    Length position = entry.position;
    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < entry.tree->child_count; i++) {
      Tree *child = entry.tree->children[i];
      Length child_left = length_add(position, child->padding);
      Length child_right = length_add(child_left, child->size);

      if (child_right.bytes > goal_position) {
        array_push(&self->path, ((TreePathEntry){
          .tree = child,
          .position = position,
          .child_index = i,
          .structural_child_index = structural_child_index,
        }));

        if (iterator_tree_is_visible(self)) {
          if (child_left.bytes > goal_position) {
            self->in_padding = true;
          } else {
            self->visible_depth++;
          }
          return true;
        }

        did_descend = true;
        break;
      }

      position = child_right;
      if (!child->extra) structural_child_index++;
    }
  } while (did_descend);

  return false;
}

static void iterator_advance(Iterator *self) {
  if (self->in_padding) {
    self->in_padding = false;
    if (iterator_tree_is_visible(self)) {
      self->visible_depth++;
    } else {
      iterator_descend(self, 0);
    }
    return;
  }

  for (;;) {
    if (iterator_tree_is_visible(self)) self->visible_depth--;
    TreePathEntry entry = array_pop(&self->path);
    if (iterator_done(self)) return;

    Tree *parent = array_back(&self->path)->tree;
    uint32_t child_index = entry.child_index + 1;
    if (parent->child_count > child_index) {
      Length position = length_add(entry.position, ts_tree_total_size(entry.tree));
      uint32_t structural_child_index = entry.structural_child_index;
      if (!entry.tree->extra) structural_child_index++;
      Tree *next_child = parent->children[child_index];

      array_push(&self->path, ((TreePathEntry){
        .tree = next_child,
        .position = position,
        .child_index = child_index,
        .structural_child_index = structural_child_index,
      }));

      if (iterator_tree_is_visible(self)) {
        if (next_child->padding.bytes > 0) {
          self->in_padding = true;
        } else {
          self->visible_depth++;
        }
      } else {
        iterator_descend(self, 0);
      }
      break;
    }
  }
}

typedef enum {
  IteratorDiffers,
  IteratorMayDiffer,
  IteratorMatches,
} IteratorComparison;

IteratorComparison iterator_compare(const Iterator *old_iter, const Iterator *new_iter) {
  Tree *old_tree, *new_tree;
  uint32_t old_start, new_start;
  TSSymbol old_alias_symbol, new_alias_symbol;
  iterator_get_visible_state(old_iter, &old_tree, &old_alias_symbol, &old_start);
  iterator_get_visible_state(new_iter, &new_tree, &new_alias_symbol, &new_start);

  if (old_alias_symbol == new_alias_symbol) {
    if (old_start == new_start) {
      if (!old_tree->has_changes &&
          old_tree->symbol == new_tree->symbol &&
          old_tree->symbol != ts_builtin_sym_error &&
          old_tree->size.bytes == new_tree->size.bytes &&
          old_tree->parse_state != TS_TREE_STATE_NONE &&
          new_tree->parse_state != TS_TREE_STATE_NONE &&
          (old_tree->parse_state == ERROR_STATE) ==
          (new_tree->parse_state == ERROR_STATE)) {
        return IteratorMatches;
      }
    }

    if (old_tree->symbol == new_tree->symbol) {
      return IteratorMayDiffer;
    }
  }

  return IteratorDiffers;
}

// static inline void iterator_print_state(Iterator *self) {
//   TreePathEntry entry = *array_back(&self->path);
//   TSPoint start = iterator_start_position(self).extent;
//   TSPoint end = iterator_end_position(self).extent;
//   const char *name = ts_language_symbol_name(self->language, entry.tree->symbol);
//   printf(
//     "(%-25s %s\t depth:%u [%u, %u] - [%u, %u])",
//     name, self->in_padding ? "(p)" : "   ",
//     self->visible_depth,
//     start.row, start.column,
//     end.row, end.column
//   );
// }

unsigned ts_tree_get_changed_ranges(Tree *old_tree, Tree *new_tree,
                                    TreePath *path1, TreePath *path2,
                                    const TSLanguage *language, TSRange **ranges) {
  RangeArray results = array_new();

  Iterator old_iter = iterator_new(path1, old_tree, language);
  Iterator new_iter = iterator_new(path2, new_tree, language);

  Length position = iterator_start_position(&old_iter);
  Length next_position = iterator_start_position(&new_iter);
  if (position.bytes < next_position.bytes) {
    range_array_add(&results, position.extent, next_position.extent);
    position = next_position;
  } else if (position.bytes > next_position.bytes) {
    range_array_add(&results, next_position.extent, position.extent);
    next_position = position;
  }

  do {
    // printf("At [%-2u, %-2u] Compare ", position.extent.row, position.extent.column);
    // iterator_print_state(&old_iter);
    // printf("\tvs\t");
    // iterator_print_state(&new_iter);
    // puts("");

    bool is_changed = false;
    switch (iterator_compare(&old_iter, &new_iter)) {
      case IteratorMatches:
        next_position = iterator_end_position(&old_iter);
        break;

      case IteratorMayDiffer:
        if (iterator_descend(&old_iter, position.bytes)) {
          if (!iterator_descend(&new_iter, position.bytes)) {
            is_changed = true;
            next_position = iterator_end_position(&old_iter);
          }
        } else if (iterator_descend(&new_iter, position.bytes)) {
          is_changed = true;
          next_position = iterator_end_position(&new_iter);
        } else {
          next_position = length_min(
            iterator_end_position(&old_iter),
            iterator_end_position(&new_iter)
          );
        }
        break;

      case IteratorDiffers:
        is_changed = true;
        next_position = length_min(
          iterator_end_position(&old_iter),
          iterator_end_position(&new_iter)
        );
        break;
    }

    while (
      !iterator_done(&old_iter) &&
      iterator_end_position(&old_iter).bytes <= next_position.bytes
    ) iterator_advance(&old_iter);

    while (
      !iterator_done(&new_iter) &&
      iterator_end_position(&new_iter).bytes <= next_position.bytes
    ) iterator_advance(&new_iter);

    while (old_iter.visible_depth > new_iter.visible_depth) iterator_ascend(&old_iter);

    while (new_iter.visible_depth > old_iter.visible_depth) iterator_ascend(&new_iter);

    if (is_changed) {
      // printf(
      //   "  change: [[%u, %u] - [%u, %u]]\n",
      //   position.extent.row, position.extent.column,
      //   next_position.extent.row, next_position.extent.column
      // );

      range_array_add(&results, position.extent, next_position.extent);
    }

    position = next_position;
  } while (!iterator_done(&old_iter) && !iterator_done(&new_iter));

  *path1 = old_iter.path;
  *path2 = new_iter.path;
  *ranges = results.contents;
  return results.size;
}
