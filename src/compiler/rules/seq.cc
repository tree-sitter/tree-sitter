#include "compiler/rules/seq.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

Seq::Seq(const Rule &left, const Rule &right) :
  left(std::make_shared<Rule>(left)),
  right(std::make_shared<Rule>(right)) {}

bool Seq::operator==(const Seq &other) const {
  return left->operator==(*other.left) && right->operator==(*other.right);
}

}  // namespace rules
}  // namespace tree_sitter
