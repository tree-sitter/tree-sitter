#include "compiler/rules/symbol.h"
#include <string>
#include <map>
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::to_string;
using std::hash;

Symbol::Symbol(int index) : index(index), is_token(false) {}

Symbol::Symbol(int index, bool is_token) : index(index), is_token(is_token) {}

bool Symbol::operator==(const Symbol &other) const {
  return (other.index == index) && (other.is_token == is_token);
}

bool Symbol::operator==(const Rule &rule) const {
  auto other = rule.as<Symbol>();
  return other && this->operator==(*other);
}

size_t Symbol::hash_code() const {
  return hash<int>()(index) ^ hash<bool>()(is_token);
}

rule_ptr Symbol::copy() const {
  return std::make_shared<Symbol>(*this);
}

string Symbol::to_string() const {
  string name = is_token ? "token" : "sym";
  return "(" + name + " " + std::to_string(index) + ")";
}

bool Symbol::operator<(const Symbol &other) const {
  if (!is_token && other.is_token)
    return true;
  if (is_token && !other.is_token)
    return false;
  return (index < other.index);
}

bool Symbol::is_built_in() const {
  return index < 0;
}

void Symbol::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
