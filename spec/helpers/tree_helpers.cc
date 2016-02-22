#include "helpers/tree_helpers.h"
#include "runtime/document.h"
#include "runtime/node.h"
#include <ostream>

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
  static TSLanguage DUMMY_LANGUAGE = {};
  static TSDocument DUMMY_DOCUMENT = {};
  DUMMY_DOCUMENT.parser.language = &DUMMY_LANGUAGE;
  DUMMY_LANGUAGE.symbol_names = symbol_names;
  TSNode node;
  node.data = tree;
  return stream << string(ts_node_string(node, &DUMMY_DOCUMENT));
}

ostream &operator<<(ostream &stream, const TSNode &node) {
  return stream << string("{") << (const TSTree *)node.data <<
    string(", ") << to_string(ts_node_start_char(node)) << string("}");
}

bool operator==(const TSNode &left, const TSNode &right) {
  return ts_node_eq(left, right);
}

bool operator==(const std::vector<TSTree *> &vec, const TreeArray &array) {
  if (vec.size() != array.size)
    return false;
  for (size_t i = 0; i < array.size; i++)
    if (array.contents[i] != vec[i])
      return false;
  return true;
}

ostream &operator<<(ostream &stream, const TSLength &length) {
  return stream << "{chars:" << length.chars << ", bytes:" <<
    length.bytes << ", rows:" << length.rows << ", columns:" << length.columns << "}";
}
