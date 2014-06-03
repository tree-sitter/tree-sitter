#include "helpers/tree_helpers.h"

ts_tree ** tree_array(std::vector<ts_tree *> trees) {
    ts_tree ** result = (ts_tree **)calloc(trees.size(), sizeof(ts_tree *));
    for (size_t i = 0; i < trees.size(); i++)
        result[i] = trees[i];
    return result;
}
