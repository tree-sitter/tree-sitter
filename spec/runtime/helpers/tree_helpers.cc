#include "runtime/helpers/tree_helpers.h"

using std::string;
using std::to_string;
using std::ostream;

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

ostream &operator<<(std::ostream &stream, const TSTree *tree) {
  return stream << string(ts_tree_string(tree, symbol_names, true));;
}

ostream &operator<<(ostream &stream, const TSNode &node) {
  return stream << string("{") << (const TSTree *)node.data <<
    string(", ") << to_string(ts_node_pos(node).chars) << string("}");
}

bool operator==(const TSNode &left, const TSNode &right) {
  return ts_node_eq(left, right);
}

ostream &operator<<(ostream &stream, const TSLength &length) {
  return stream << string("{") << to_string(length.chars) << string(", ") <<
    to_string(length.bytes) << string("}");
}
