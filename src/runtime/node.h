#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"
#include "runtime/tree.h"

struct TSNode {
  size_t ref_count;
  size_t index;
  TSLength position;
  const TSTree *content;
  struct TSNode *parent;
  const char **names;
};

TSNode *ts_node_make(const TSTree *tree, TSNode *parent, size_t index,
                     TSLength position, const char **names);
TSNode *ts_node_make_root(const TSTree *tree, const char **names);

#endif
