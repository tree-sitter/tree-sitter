#ifndef RUNTIME_TREE_CURSOR_H_
#define RUNTIME_TREE_CURSOR_H_

#include "runtime/subtree.h"

typedef struct {
  Subtree *subtree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
} TreeCursorEntry;

struct TSTreeCursor {
  const TSTree *tree;
  Array(TreeCursorEntry) stack;
};

void ts_tree_cursor_init(TSTreeCursor *, const TSTree *);

#endif  // RUNTIME_TREE_CURSOR_H_
