#include "test_helper.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "runtime/document.h"
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

TreeArray *tree_array(std::vector<Tree *> trees) {
  static TreeArray result;
  result.capacity = trees.size();
  result.size = trees.size();
  result.contents = (Tree **)calloc(trees.size(), sizeof(Tree *));
  for (size_t i = 0; i < trees.size(); i++) {
    result.contents[i] = trees[i];
  }
  return &result;
}

ostream &operator<<(std::ostream &stream, const Tree *tree) {
  static TSLanguage DUMMY_LANGUAGE = {};
  DUMMY_LANGUAGE.symbol_names = symbol_names;
  char *string = ts_tree_string(tree, &DUMMY_LANGUAGE, false);
  stream << string;
  ts_free(string);
  return stream;
}

ostream &operator<<(ostream &stream, const TSNode &node) {
  if (node.subtree) {
    char *string = ts_node_string(node, node.document);
    stream << "{" << string << ", " << to_string(ts_node_start_byte(node)) << "}";
    ts_free(string);
    return stream;
  } else {
    return stream << "NULL";
  }
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

void assert_consistent_tree_sizes(TSNode node) {
  uint32_t child_count = ts_node_child_count(node);
  uint32_t named_child_count = ts_node_named_child_count(node);
  uint32_t start_byte = ts_node_start_byte(node);
  uint32_t end_byte = ts_node_end_byte(node);
  TSPoint start_point = ts_node_start_point(node);
  TSPoint end_point = ts_node_end_point(node);

  AssertThat(start_byte, !IsGreaterThan(end_byte));
  AssertThat(start_point, !IsGreaterThan(end_point));

  size_t last_child_end_byte = start_byte;
  TSPoint last_child_end_point = start_point;

  bool some_child_has_changes = false;
  size_t actual_named_child_count = 0;
  for (size_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    uint32_t child_start_byte = ts_node_start_byte(child);
    TSPoint child_start_point = ts_node_start_point(child);

    AssertThat(child_start_byte, !IsLessThan(last_child_end_byte));
    AssertThat(child_start_point, !IsLessThan(last_child_end_point));
    assert_consistent_tree_sizes(child);

    if (ts_node_has_changes(child)) some_child_has_changes = true;
    if (ts_node_is_named(child)) actual_named_child_count++;

    last_child_end_byte = ts_node_end_byte(child);
    last_child_end_point = ts_node_end_point(child);
  }

  AssertThat(actual_named_child_count, Equals(named_child_count));

  if (child_count > 0) {
    AssertThat(end_byte, !IsLessThan(last_child_end_byte));
    AssertThat(end_point, !IsLessThan(last_child_end_point));
  }

  if (some_child_has_changes) {
    AssertThat(ts_node_has_changes(node), IsTrue());
  }
}
