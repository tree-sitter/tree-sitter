#ifndef RUNTIME_GET_CHANGED_RANGES_H_
#define RUNTIME_GET_CHANGED_RANGES_H_

#include "runtime/tree.h"

typedef struct {
  Tree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
} TreePathEntry;

typedef Array(TreePathEntry) TreePath;

unsigned ts_tree_get_changed_ranges(
  Tree *old_tree, Tree *new_tree, TreePath *path1, TreePath *path2,
  const TSLanguage *language, TSRange **ranges
);

#endif  // RUNTIME_GET_CHANGED_RANGES_H_
