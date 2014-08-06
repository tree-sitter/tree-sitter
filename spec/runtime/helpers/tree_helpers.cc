#include "runtime/helpers/tree_helpers.h"

TSTree ** tree_array(std::vector<TSTree *> trees) {
  TSTree ** result = (TSTree **)calloc(trees.size(), sizeof(TSTree *));
  for (size_t i = 0; i < trees.size(); i++)
      result[i] = trees[i];
  return result;
}
