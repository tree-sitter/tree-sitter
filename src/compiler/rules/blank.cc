#include "compiler/rules/blank.h"
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace rules {

Blank::Blank() {}

bool Blank::operator==(const Rule &rule) const {
  return dynamic_cast<const Blank *>(&rule) != nullptr;
}

size_t Blank::hash_code() const { return 0; }

rule_ptr Blank::copy() const { return std::make_shared<Blank>(); }

std::string Blank::to_string() const { return "#<blank>"; }

void Blank::accept(Visitor *visitor) const { visitor->visit(this); }

}  // namespace rules
}  // namespace tree_sitter
