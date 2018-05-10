#ifndef RUNTIME_TREE_CURSOR_H_
#define RUNTIME_TREE_CURSOR_H_

#include "runtime/subtree.h"

typedef struct {
  Subtree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
} TreeCursorEntry;

struct TSTreeCursor {
  const TSDocument *document;
  Array(TreeCursorEntry) stack;
};

TSTreeCursor *ts_tree_cursor_new(const TSDocument *);

#endif  // RUNTIME_TREE_CURSOR_H_
