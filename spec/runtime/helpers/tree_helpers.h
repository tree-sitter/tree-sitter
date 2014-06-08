#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "tree_sitter/runtime.h"

#include <vector>

ts_tree ** tree_array(std::vector<ts_tree *> trees);

#endif  // HELPERS_TREE_HELPERS_H_