#include "compiler/rules/metadata.h"
#include <climits>
#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

using std::move;
using std::string;

bool Alias::operator==(const Alias &other) const {
  return value == other.value && is_named == other.is_named;
}

bool Alias::operator!=(const Alias &other) const {
  return !operator==(other);
}

bool Alias::operator<(const Alias &other) const {
  if (value < other.value) return true;
  if (other.value < value) return false;
  return is_named < other.is_named;
}

Metadata::Metadata(const Rule &rule, MetadataParams params) :
  rule(std::make_shared<Rule>(rule)), params(params) {}

bool Metadata::operator==(const Metadata &other) const {
  return rule->operator==(*other.rule) && params == other.params;
}

Metadata Metadata::token(const Rule &rule) {
  MetadataParams params;
  params.is_token = true;
  return Metadata{rule, params};
}

Metadata Metadata::active_prec(int precedence, const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = precedence;
  params.is_active = true;
  return Metadata{rule, params};
}

Metadata Metadata::prec(int precedence, const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = precedence;
  return Metadata{rule, params};
}

Metadata Metadata::prec_left(int precedence, const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = precedence;
  params.has_associativity = true;
  params.associativity = AssociativityLeft;
  return Metadata{rule, params};
}

Metadata Metadata::prec_right(int precedence, const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = precedence;
  params.has_associativity = true;
  params.associativity = AssociativityRight;
  return Metadata{rule, params};
}

Metadata Metadata::prec_dynamic(int dynamic_precedence, const Rule &rule) {
  MetadataParams params;
  params.dynamic_precedence = dynamic_precedence;
  return Metadata{rule, params};
}

Metadata Metadata::separator(const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = INT_MIN;
  params.is_active = true;
  return Metadata{rule, params};
}

Metadata Metadata::main_token(const Rule &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = 0;
  params.is_main_token = true;
  return Metadata{rule, params};
}

Metadata Metadata::alias(string &&value, bool is_named, const Rule &rule) {
  MetadataParams params;
  params.alias = {move(value), is_named};
  return Metadata{rule, params};
}

}  // namespace rules
}  // namespace tree_sitter
