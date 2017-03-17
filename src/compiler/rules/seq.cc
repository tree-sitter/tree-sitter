#include "compiler/rules/seq.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

Seq::Seq(const Rule &left, const Rule &right) :
  left(std::make_shared<Rule>(left)),
  right(std::make_shared<Rule>(right)) {}

std::shared_ptr<Rule> Seq::build(const std::vector<Rule> &rules) {
  Rule result;
  for (const auto &rule : rules) {
    rule.match(
      [](Blank) {},
      [&](Metadata metadata) {
        if (!metadata.rule->is<Blank>()) {
          result = Seq{result, rule};
        }
      },
      [&](auto) {
        if (result.is<Blank>()) {
          result = rule;
        } else {
          result = Seq{result, rule};
        }
      }
    );
  }
  return std::make_shared<Rule>(result);
}

bool Seq::operator==(const Seq &other) const {
  return left->operator==(*other.left) && right->operator==(*other.right);
}

}  // namespace rules
}  // namespace tree_sitter
