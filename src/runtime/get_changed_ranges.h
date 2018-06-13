#ifndef RUNTIME_GET_CHANGED_RANGES_H_
#define RUNTIME_GET_CHANGED_RANGES_H_

#include "runtime/tree_cursor.h"
#include "runtime/subtree.h"

unsigned ts_subtree_get_changed_ranges(
  const Subtree *old_tree, const Subtree *new_tree,
  TreeCursor *cursor1, TreeCursor *cursor2,
  const TSLanguage *language, TSRange **ranges
);

#endif  // RUNTIME_GET_CHANGED_RANGES_H_
