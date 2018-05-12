#ifndef RUNTIME_GET_CHANGED_RANGES_H_
#define RUNTIME_GET_CHANGED_RANGES_H_

#include "runtime/subtree.h"

unsigned ts_subtree_get_changed_ranges(
  const Subtree *old_tree, const Subtree *new_tree,
  TSTreeCursor *cursor1, TSTreeCursor *cursor2,
  const TSLanguage *language, TSRange **ranges
);

#endif  // RUNTIME_GET_CHANGED_RANGES_H_
