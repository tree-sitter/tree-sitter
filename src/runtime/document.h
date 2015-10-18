#ifndef RUNTIME_DOCUMENT_H_
#define RUNTIME_DOCUMENT_H_

#include "tree_sitter/parser.h"
#include "runtime/parser.h"
#include "runtime/tree.h"
#include <stdbool.h>

struct TSDocument {
  TSParser parser;
  TSInput input;
  TSTree *tree;
  size_t parse_count;
  bool valid;
};

#endif
