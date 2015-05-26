#ifndef HELPERS_TREE_HELPERS_H_
#define HELPERS_TREE_HELPERS_H_

#include "runtime/tree.h"
#include <vector>
#include <string>

TSTree ** tree_array(std::vector<TSTree *> trees);

struct EqualsTree {
  EqualsTree(const TSTree *expected, const char **symbol_names);
  bool Matches(const TSTree *actual) const;
  const TSTree *expected;
  const char **symbol_names;
};

std::ostream &operator<<(std::ostream &stream, const EqualsTree &matcher);

#endif  // HELPERS_TREE_HELPERS_H_
