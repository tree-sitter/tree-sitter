#include "compiler/build_tables/parse_item.h"
#include <string>
#include "compiler/syntax_grammar.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::to_string;
using std::ostream;
using rules::Symbol;

ParseItem::ParseItem(const Symbol &lhs, unsigned int production_index,
                     unsigned int step_index, int rule_id)
    : variable_index(lhs.index),
      production_index(production_index),
      step_index(step_index),
      rule_id(rule_id) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (variable_index == other.variable_index) &&
         (rule_id == other.rule_id) && (step_index == other.step_index);
}

bool ParseItem::operator<(const ParseItem &other) const {
  if (variable_index < other.variable_index)
    return true;
  if (variable_index > other.variable_index)
    return false;
  if (step_index < other.step_index)
    return true;
  if (step_index > other.step_index)
    return false;
  return rule_id < other.rule_id;
}

Symbol ParseItem::lhs() const {
  return Symbol(variable_index);
}

}  // namespace build_tables
}  // namespace tree_sitter
