#include "compiler/rules/repeat.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

Repeat::Repeat(const Rule &rule) :
  rule(std::make_shared<Rule>(rule)) {}

bool Repeat::operator==(const Repeat &other) const {
  return rule->operator==(*other.rule);
}

}  // namespace rules
}  // namespace tree_sitter
