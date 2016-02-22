#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "runtime/tree.h"
#include <vector>
#include <string>

TSTree ** tree_array(std::vector<TSTree *> trees);

std::ostream &operator<<(std::ostream &stream, const TSTree *tree);
std::ostream &operator<<(std::ostream &stream, const TSNode &node);
std::ostream &operator<<(std::ostream &stream, const TSLength &length);
bool operator==(const TSNode &left, const TSNode &right);
bool operator==(const std::vector<TSTree *> &right, const TreeArray &array);

#endif  // HELPERS_TREE_HELPERS_H_
