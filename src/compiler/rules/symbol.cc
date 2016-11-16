#include "compiler/rules/symbol.h"
#include <string>
#include <map>
#include "compiler/rules/visitor.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::to_string;
using util::hash_combine;

Symbol::Symbol(Symbol::Index index) : index(index), is_token(false) {}

Symbol::Symbol(Symbol::Index index, bool is_token) : index(index), is_token(is_token) {}

bool Symbol::operator==(const Symbol &other) const {
  return (other.index == index) && (other.is_token == is_token);
}

bool Symbol::operator==(const Rule &rule) const {
  auto other = rule.as<Symbol>();
  return other && this->operator==(*other);
}

size_t Symbol::hash_code() const {
  size_t result = 0;
  hash_combine(&result, index);
  hash_combine(&result, is_token);
  return result;
}

rule_ptr Symbol::copy() const {
  return std::make_shared<Symbol>(*this);
}

string Symbol::to_string() const {
  string name = is_token ? "token" : "sym";
  return "(" + name + " " + std::to_string(index) + ")";
}

bool Symbol::operator<(const Symbol &other) const {
  if (is_token && !other.is_token)
    return true;
  if (!is_token && other.is_token)
    return false;
  return (index < other.index);
}

bool Symbol::is_built_in(Symbol::Index index) {
  return index < 0;
}

bool Symbol::is_built_in() const {
  return is_built_in(index);
}

void Symbol::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
