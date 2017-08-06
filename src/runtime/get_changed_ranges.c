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
} Iterator;

static Iterator iterator_new(TreePath *path, Tree *tree, const TSLanguage *language) {
  array_clear(path);
  array_push(path, ((TreePathEntry){
    .tree = tree,
    .position = { 0, 0, { 0, 0 } },
    .child_index = 0,
    .structural_child_index = 0,
  }));
  return (Iterator) {
    .path = *path,
    .language = language,
    .visible_depth = 1,
  };
}

Length iterator_start_position(Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  return length_add(entry.position, entry.tree->padding);
}

Length iterator_end_position(Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  return length_add(length_add(entry.position, entry.tree->padding), entry.tree->size);
}

static bool iterator_done(Iterator *self) {
  return self->path.size == 0;
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

static void iterator_print_state(Iterator *self) {
  TreePathEntry entry = *array_back(&self->path);
  TSPoint start = point_add(entry.position.extent, entry.tree->padding.extent);
  TSPoint end = point_add(start, entry.tree->size.extent);
  const char *name = ts_language_symbol_name(self->language, entry.tree->symbol);
  printf("(%-25s\t depth:%u [%u, %u] - [%u, %u])", name, self->visible_depth, start.row, start.column, end.row, end.column);
}

static void iterator_ascend(Iterator *self) {
  bool did_ascend = false;
  for (;;) {
    if (iterator_done(self)) break;
    if (iterator_tree_is_visible(self)) {
      if (did_ascend) break;
      did_ascend = true;
      self->visible_depth--;
    }
    self->path.size--;
  }
}

static bool iterator_descend(Iterator *self, Length position) {
  uint32_t original_size = self->path.size;

  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(&self->path);
    Length child_left = entry.position;
    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < entry.tree->child_count; i++) {
      Tree *child = entry.tree->children[i];
      Length child_right = length_add(child_left, ts_tree_total_size(child));

      if (child_right.bytes > position.bytes) {
        array_push(&self->path, ((TreePathEntry){
          .tree = child,
          .position = child_left,
          .child_index = i,
          .structural_child_index = structural_child_index,
        }));

        if (iterator_tree_is_visible(self)) {
          self->visible_depth++;
          return true;
        }

        if (child->visible_child_count > 0) {
          did_descend = true;
          break;
        }

        self->path.size--;
      }

      child_left = child_right;
      if (!child->extra) structural_child_index++;
    }
  } while (did_descend);

  self->path.size = original_size;
  return false;
}

static bool iterator_advance(Iterator *self) {
  if (iterator_done(self)) return false;

  for (;;) {
    if (iterator_tree_is_visible(self)) self->visible_depth--;
    TreePathEntry entry = array_pop(&self->path);
    if (iterator_done(self)) return false;

    Tree *parent = array_back(&self->path)->tree;
    Length position = length_add(entry.position, ts_tree_total_size(entry.tree));
    uint32_t structural_child_index = entry.structural_child_index;
    if (!entry.tree->extra) structural_child_index++;

    for (uint32_t i = entry.child_index + 1; i < parent->child_count; i++) {
      Tree *next_child = parent->children[i];
      array_push(&self->path, ((TreePathEntry){
        .tree = next_child,
        .position = position,
        .child_index = i,
        .structural_child_index = structural_child_index,
      }));

      if (iterator_tree_is_visible(self)) {
        self->visible_depth++;
        return true;
      }

      if (next_child->visible_child_count > 0) {
        iterator_descend(self, length_zero());
        return true;
      }

      if (next_child->child_count == 0) {
        return true;
      }

      self->path.size--;
      position = length_add(position, ts_tree_total_size(next_child));
      if (!next_child->extra) structural_child_index++;
    }
  }
}

typedef enum {
  IteratorDiffers,
  IteratorMayDiffer,
  IteratorMatches,
} IteratorComparison;

IteratorComparison iterator_compare(const Iterator *self, const Iterator *other) {
  Tree *old_tree = NULL;
  TSSymbol old_alias_symbol = 0;
  Length old_start = length_zero();
  for (uint32_t i = self->path.size - 1; i + 1 > 0; i--) {
    old_tree = self->path.contents[i].tree;
    old_start = self->path.contents[i].position;
    if (i > 0) {
      Tree *parent = self->path.contents[i - 1].tree;
      const TSSymbol *alias_sequence = ts_language_alias_sequence(self->language, parent->alias_sequence_id);
      if (alias_sequence) {
        old_alias_symbol = alias_sequence[self->path.contents[i].structural_child_index];
      }
    }

    if (old_tree->visible || old_alias_symbol) break;
  }

  Tree *new_tree = NULL;
  TSSymbol new_alias_symbol = 0;
  Length new_start = length_zero();
  for (uint32_t i = other->path.size - 1; i + 1 > 0; i--) {
    new_tree = other->path.contents[i].tree;
    new_start = other->path.contents[i].position;
    if (i > 0) {
      Tree *parent = other->path.contents[i - 1].tree;
      const TSSymbol *alias_sequence = ts_language_alias_sequence(self->language, parent->alias_sequence_id);
      if (alias_sequence) {
        new_alias_symbol = alias_sequence[other->path.contents[i].structural_child_index];
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
        return IteratorMatches;
      }
    }

    if (old_tree->symbol == new_tree->symbol) {
      return IteratorMayDiffer;
    }
  }

  return IteratorDiffers;
}

unsigned ts_tree_get_changed_ranges(Tree *old_tree, Tree *new_tree,
                                    TreePath *path1, TreePath *path2,
                                    const TSLanguage *language, TSRange **ranges) {
  Iterator old_iter = iterator_new(path1, old_tree, language);
  Iterator new_iter = iterator_new(path2, new_tree, language);
  RangeArray results = array_new();
  Length position = length_zero();

  while (!iterator_done(&old_iter) && !iterator_done(&new_iter)) {
    bool is_changed = false;
    Length next_position = position;
    Length old_start = iterator_start_position(&old_iter);
    Length new_start = iterator_start_position(&new_iter);
    Length old_end = iterator_end_position(&old_iter);
    Length new_end = iterator_end_position(&new_iter);

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
      // printf("At [%-2u, %-2u] Compare ", position.extent.row, position.extent.column);
      // iterator_print_state(&old_iter);
      // printf("\tvs\t");
      // iterator_print_state(&new_iter);
      // printf("\n");

      switch (iterator_compare(&old_iter, &new_iter)) {
        case IteratorMatches:
          next_position = old_end;
          break;

        case IteratorMayDiffer:
          next_position = length_min(old_end, new_end);
          if (iterator_descend(&old_iter, position)) {
            if (iterator_descend(&new_iter, position)) {
              next_position = position;
            } else {
              iterator_ascend(&old_iter);
              is_changed = true;
            }
          } else if (iterator_descend(&new_iter, position)) {
            iterator_ascend(&new_iter);
            is_changed = true;
          }
          break;

        case IteratorDiffers:
          next_position = length_min(old_end, new_end);
          is_changed = true;
          break;
      }
    }

    while (old_end.bytes <= next_position.bytes && iterator_advance(&old_iter)) {
      old_end = iterator_end_position(&old_iter);
    }

    while (new_end.bytes <= next_position.bytes && iterator_advance(&new_iter)) {
      new_end = iterator_end_position(&new_iter);
    }

    while (old_iter.visible_depth > new_iter.visible_depth) {
      iterator_ascend(&old_iter);
    }

    while (new_iter.visible_depth > old_iter.visible_depth) {
      iterator_ascend(&new_iter);
    }

    if (is_changed) {
      // printf(
      //   "  changed range: [[%u, %u] - [%u, %u]]\n",
      //   position.extent.row, position.extent.column,
      //   next_position.extent.row, next_position.extent.column
      // );

      range_array_add(&results, position.extent, next_position.extent);
    }

    position = next_position;
  }

  *path1 = old_iter.path;
  *path2 = new_iter.path;
  *ranges = results.contents;
  return results.size;
}
