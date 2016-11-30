#include "compiler/rules/external_token.h"
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::hash;

ExternalToken::ExternalToken(const string &name) : name(name) {}

rule_ptr ExternalToken::build(const string &name) {
  return std::make_shared<ExternalToken>(name);
}

bool ExternalToken::operator==(const Rule &rule) const {
  auto other = rule.as<ExternalToken>();
  return other && other->name == name;
}

size_t ExternalToken::hash_code() const {
  return hash<string>()(name);
}

rule_ptr ExternalToken::copy() const {
  return std::make_shared<ExternalToken>(*this);
}

string ExternalToken::to_string() const {
  return string("(sym '") + name + "')";
}

void ExternalToken::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
