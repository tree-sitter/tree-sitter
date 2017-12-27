#ifndef RUNTIME_DOCUMENT_H_
#define RUNTIME_DOCUMENT_H_

#include "runtime/parser.h"
#include "runtime/tree.h"
#include "runtime/get_changed_ranges.h"
#include <stdbool.h>

struct TSDocument {
  Parser parser;
  TSInput input;
  Tree *tree;
  TreePath tree_path1;
  TreePath tree_path2;
  size_t parse_count;
  bool valid;
  bool owns_input;
};

#endif
