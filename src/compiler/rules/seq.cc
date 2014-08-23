#include "compiler/rules/seq.h"
#include <string>
#include "compiler/rules/visitor.h"
#include "compiler/rules/blank.h"

namespace tree_sitter {
namespace rules {

using std::make_shared;
using std::string;
using std::vector;

Seq::Seq(rule_ptr left, rule_ptr right) : left(left), right(right) {}

rule_ptr Seq::Build(const std::vector<rule_ptr> &rules) {
  rule_ptr result = make_shared<Blank>();
  for (auto &rule : rules)
    result = (typeid(*result) != typeid(Blank)) ? make_shared<Seq>(result, rule)
                                                : rule;
  return result;
}

bool Seq::operator==(const Rule &rule) const {
  const Seq *other = dynamic_cast<const Seq *>(&rule);
  return other && (*other->left == *left) && (*other->right == *right);
}

size_t Seq::hash_code() const { return left->hash_code() ^ right->hash_code(); }

rule_ptr Seq::copy() const { return std::make_shared<Seq>(*this); }

string Seq::to_string() const {
  return string("(seq ") + left->to_string() + " " + right->to_string() + ")";
}

void Seq::accept(Visitor *visitor) const { visitor->visit(this); }

}  // namespace rules
}  // namespace tree_sitter
