#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"
#include "runtime/tree.h"

struct TSNode {
  size_t ref_count;
  size_t start_position;
  size_t index;
  const TSTree *content;
  struct TSNode *parent;
  const char **names;
};

TSNode *ts_node_make(const TSTree *tree, TSNode *parent, size_t index,
                     size_t start_position, const char **names);
TSNode *ts_node_make_root(const TSTree *tree, const char **names);

#endif
