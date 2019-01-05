#ifndef RUNTIME_TREE_CURSOR_H_
#define RUNTIME_TREE_CURSOR_H_

#include "runtime/subtree.h"

typedef struct {
  const Subtree *subtree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
} TreeCursorEntry;

typedef struct {
  const TSTree *tree;
  Array(TreeCursorEntry) stack;
} TreeCursor;

void ts_tree_cursor_init(TreeCursor *, TSNode);

#endif  // RUNTIME_TREE_CURSOR_H_
