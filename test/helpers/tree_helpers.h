#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "runtime/subtree.h"
#include <vector>
#include <string>

extern const char *symbol_names[24];
SubtreeArray *tree_array(std::vector<Subtree> trees);

std::ostream &operator<<(std::ostream &stream, Subtree tree);
std::ostream &operator<<(std::ostream &stream, const TSNode &node);
bool operator==(const TSNode &left, const TSNode &right);
bool operator==(const std::vector<Subtree> &right, const SubtreeArray &array);
std::string to_string(const TSTree *);

void assert_consistent_tree_sizes(const TSTree *, const std::string &);

#endif  // HELPERS_TREE_HELPERS_H_
