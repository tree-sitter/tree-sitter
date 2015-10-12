#include "compiler/rules/named_symbol.h"
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::hash;

NamedSymbol::NamedSymbol(const std::string &name) : name(name) {}

bool NamedSymbol::operator==(const Rule &rule) const {
  auto other = rule.as<NamedSymbol>();
  return other && other->name == name;
}

size_t NamedSymbol::hash_code() const {
  return hash<string>()(name);
}

rule_ptr NamedSymbol::copy() const {
  return std::make_shared<NamedSymbol>(*this);
}

string NamedSymbol::to_string() const {
  return string("(sym '") + name + "')";
}

void NamedSymbol::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
