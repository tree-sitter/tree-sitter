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

Symbol::Symbol(Symbol::Index index, Symbol::Type type) : index(index), type(type) {}

bool Symbol::operator==(const Symbol &other) const {
  return (other.index == index) && (other.type == type);
}

bool Symbol::operator==(const Rule &rule) const {
  auto other = rule.as<Symbol>();
  return other && this->operator==(*other);
}

size_t Symbol::hash_code() const {
  size_t result = 0;
  hash_combine(&result, index);
  hash_combine<int>(&result, type);
  return result;
}

rule_ptr Symbol::copy() const {
  return std::make_shared<Symbol>(*this);
}

string Symbol::to_string() const {
  switch (type) {
    case Symbol::Terminal:
      return "(terminal " + std::to_string(index) + ")";
    case Symbol::NonTerminal:
      return "(non-terminal " + std::to_string(index) + ")";
    case Symbol::External:
      return "(external " + std::to_string(index) + ")";
    default:
      return "(none)";
  }
}

bool Symbol::operator<(const Symbol &other) const {
  if (type < other.type)
    return true;
  if (other.type < type)
    return false;
  return (index < other.index);
}

bool Symbol::is_built_in(Symbol::Index index) {
  return index < 0;
}

bool Symbol::is_built_in() const {
  return is_built_in(index);
}

bool Symbol::is_token() const {
  return type == Symbol::Terminal;
}

bool Symbol::is_external() const {
  return type == Symbol::External;
}

bool Symbol::is_non_terminal() const {
  return type == Symbol::NonTerminal;
}

void Symbol::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
