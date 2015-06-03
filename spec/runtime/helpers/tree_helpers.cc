#include "runtime/helpers/tree_helpers.h"

const char *symbol_names[12] = {
  "ERROR", "END", "DOCUMENT", "AMBIGUITY",
  "zero", "one", "two", "three", "four", "five", "six", "seven",
};

TSTree ** tree_array(std::vector<TSTree *> trees) {
  TSTree ** result = (TSTree **)calloc(trees.size(), sizeof(TSTree *));
  for (size_t i = 0; i < trees.size(); i++)
      result[i] = trees[i];
  return result;
}

EqualsTree::EqualsTree(const TSTree *expected, const char **symbol_names)
  : expected(expected), symbol_names(symbol_names) {}

bool EqualsTree::Matches(const TSTree *actual) const {
  return ts_tree_eq(actual, expected);
}

std::ostream &operator<<(std::ostream &stream, const EqualsTree &matcher) {
  stream << std::string("equals tree: ") << std::string(ts_tree_string(matcher.expected, matcher.symbol_names));
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const TSTree *tree) {
  return stream << std::string(ts_tree_string(tree, symbol_names));;
}
