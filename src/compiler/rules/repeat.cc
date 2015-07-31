#include "compiler/rules/repeat.h"
#include <memory>
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace rules {

using std::dynamic_pointer_cast;
using std::make_shared;
using std::string;

Repeat::Repeat(const rule_ptr content) : content(content) {}

rule_ptr Repeat::build(const rule_ptr &rule) {
  auto inner_repeat = dynamic_pointer_cast<Repeat>(rule);
  if (inner_repeat.get())
    return inner_repeat;
  else
    return make_shared<Repeat>(rule);
}

bool Repeat::operator==(const Rule &rule) const {
  const Repeat *other = dynamic_cast<const Repeat *>(&rule);
  return other && (*other->content == *content);
}

size_t Repeat::hash_code() const {
  return content->hash_code();
}

rule_ptr Repeat::copy() const {
  return make_shared<Repeat>(*this);
}

string Repeat::to_string() const {
  return string("(repeat ") + content->to_string() + ")";
}

void Repeat::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
