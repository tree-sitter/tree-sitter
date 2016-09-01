#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"
#include "runtime/tree.h"

TSNode ts_node_make(const TSTree *, size_t character, size_t byte, size_t row);

#endif
