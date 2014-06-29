#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "tree_sitter/runtime.h"

#include <vector>

TSTree ** tree_array(std::vector<TSTree *> trees);

#endif  // HELPERS_TREE_HELPERS_H_