#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "runtime/tree.h"
#include <vector>
#include <string>

extern const char *symbol_names[24];
TreeArray *tree_array(std::vector<Tree *> trees);

std::ostream &operator<<(std::ostream &stream, const Tree *tree);
std::ostream &operator<<(std::ostream &stream, const TSNode &node);
bool operator==(const TSNode &left, const TSNode &right);
bool operator==(const std::vector<Tree *> &right, const TreeArray &array);

void assert_consistent_tree_sizes(TSNode node);

#endif  // HELPERS_TREE_HELPERS_H_
