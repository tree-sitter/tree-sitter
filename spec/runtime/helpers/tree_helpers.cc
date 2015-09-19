#include "runtime/helpers/tree_helpers.h"

static const char *symbol_names[24] = {
  "ERROR", "END",  "two", "three", "four", "five", "six", "seven", "eight",
  "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
  "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "twenty-one",
  "twenty-two", "twenty-three"
};

TSTree ** tree_array(std::vector<TSTree *> trees) {
  TSTree ** result = (TSTree **)calloc(trees.size(), sizeof(TSTree *));
  for (size_t i = 0; i < trees.size(); i++)
      result[i] = trees[i];
  return result;
}

std::ostream &operator<<(std::ostream &stream, const TSTree *tree) {
  return stream << std::string(ts_tree_string(tree, symbol_names));;
}

std::ostream &operator<<(std::ostream &stream, const TSNode node) {
  return stream << std::string("{") << (const TSTree *)node.data <<
    std::string(", ") << std::to_string(ts_node_pos(node).chars) << std::string("}");
}

bool operator==(const TSNode &left, const TSNode &right) {
  return ts_node_eq(left, right);
}
