#include "compiler/rules/pattern.h"
#include <string>
#include "compiler/rules/visitor.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::hash;

Pattern::Pattern(const string &string) : value(string) {}

bool Pattern::operator==(tree_sitter::rules::Rule const &other) const {
  auto pattern = dynamic_cast<const Pattern *>(&other);
  return pattern && (pattern->value == value);
}

size_t Pattern::hash_code() const {
  return hash<string>()(value);
}

rule_ptr Pattern::copy() const {
  return std::make_shared<Pattern>(*this);
}

string Pattern::to_string() const {
  return string("(pattern '") + util::escape_string(value) + "')";
}

void Pattern::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
