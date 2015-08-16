#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "tree_sitter/parser.h"
#include "runtime/length.h"
#include "runtime/tree.h"

TSNode ts_node_make(const TSTree *, TSLength);

static inline TSNode ts_node_null() {
  return (TSNode){.data = NULL, .offset = ts_length_zero() };
}

#endif
