#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"
#include "runtime/length.h"
#include "runtime/tree.h"

TSNode ts_node_make(const TSTree *, TSLength);

#endif
