#include "compiler/rules/metadata.h"
#include <string>
#include <map>
#include "compiler/rules/visitor.h"
#include "compiler/rules/blank.h"

namespace tree_sitter {
namespace rules {

using std::hash;
using std::make_shared;
using std::map;
using std::pair;

Metadata::Metadata(rule_ptr rule, map<MetadataKey, int> values)
    : rule(rule), value(values) {}

rule_ptr Metadata::build(rule_ptr rule, map<MetadataKey, int> values) {
  return std::make_shared<Metadata>(rule, values);
}

bool Metadata::operator==(const Rule &rule) const {
  auto other = rule.as<Metadata>();
  return other && other->value == value && other->rule->operator==(*this->rule);
}

size_t Metadata::hash_code() const {
  size_t result = hash<size_t>()(value.size());
  for (auto &pair : value) {
    result ^= hash<int>()(pair.first);
    result ^= hash<int>()(pair.second);
  }
  return result;
}

rule_ptr Metadata::copy() const {
  return make_shared<Metadata>(rule->copy(), value);
}

pair<int, bool> Metadata::value_for(MetadataKey key) const {
  auto entry = value.find(key);
  if (entry == value.end())
    return { 0, false };
  else
    return { entry->second, true };
}

std::string Metadata::to_string() const {
  auto precedence = value_for(rules::PRECEDENCE);
  if (precedence.second && value_for(rules::IS_ACTIVE).second)
    return "(metadata prec:" + std::to_string(precedence.first) + " " +
           rule->to_string() + ")";
  else
    return "(metadata " + rule->to_string() + ")";
}

void Metadata::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
