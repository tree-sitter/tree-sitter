#include "helpers/tree_helpers.h"
#include "runtime/document.h"
#include "runtime/node.h"
#include <ostream>

using std::string;
using std::to_string;
using std::ostream;

const char *symbol_names[24] = {
  "ERROR", "END",  "two", "three", "four", "five", "six", "seven", "eight",
  "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
  "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "twenty-one",
  "twenty-two", "twenty-three"
};

Tree ** tree_array(std::vector<Tree *> trees) {
  Tree ** result = (Tree **)calloc(trees.size(), sizeof(Tree *));
  for (size_t i = 0; i < trees.size(); i++)
      result[i] = trees[i];
  return result;
}

ostream &operator<<(std::ostream &stream, const Tree *tree) {
  static TSLanguage DUMMY_LANGUAGE = {};
  static TSDocument DUMMY_DOCUMENT = {};
  DUMMY_DOCUMENT.parser.language = &DUMMY_LANGUAGE;
  DUMMY_LANGUAGE.symbol_names = symbol_names;
  TSNode node;
  node.data = tree;
  return stream << string(ts_node_string(node, &DUMMY_DOCUMENT));
}

ostream &operator<<(ostream &stream, const TSNode &node) {
  return stream << string("{") << (const Tree *)node.data <<
    string(", ") << to_string(ts_node_start_char(node)) << string("}");
}

bool operator==(const TSNode &left, const TSNode &right) {
  return ts_node_eq(left, right);
}

bool operator==(const std::vector<Tree *> &vec, const TreeArray &array) {
  if (vec.size() != array.size)
    return false;
  for (size_t i = 0; i < array.size; i++)
    if (array.contents[i] != vec[i])
      return false;
  return true;
}
