#include "compiler/rules/metadata.h"
#include <string>
#include <map>
#include <climits>
#include "compiler/rules/visitor.h"
#include "compiler/rules/blank.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace rules {

using std::make_shared;
using std::map;
using std::pair;
using util::hash_combine;

MetadataParams::MetadataParams() :
  precedence{0},
  associativity{AssociativityNone},
  has_precedence{false},
  has_associativity{false},
  is_token{false},
  is_string{false},
  is_active{false},
  is_main_token{false} {}

bool MetadataParams::operator==(const MetadataParams &other) const {
  return
    precedence == other.precedence &&
    associativity == other.associativity &&
    has_precedence == other.has_precedence &&
    has_associativity == other.has_associativity &&
    is_token == other.is_token &&
    is_string == other.is_string &&
    is_active == other.is_active &&
    is_main_token == other.is_main_token;
}

Metadata::Metadata(rule_ptr rule, MetadataParams params)
    : rule(rule), params(params) {}

rule_ptr Metadata::build(rule_ptr rule, MetadataParams params) {
  return std::make_shared<Metadata>(rule, params);
}

rule_ptr Metadata::main_token(rule_ptr rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = 0;
  params.is_main_token = true;
  return Metadata::build(rule, params);
}

rule_ptr Metadata::separator(rule_ptr rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = INT_MIN;
  params.is_active = true;
  return Metadata::build(rule, params);
}

bool Metadata::operator==(const Rule &rule) const {
  auto other = rule.as<Metadata>();
  return other && other->params == params && other->rule->operator==(*this->rule);
}

size_t Metadata::hash_code() const {
  size_t result = 0;
  hash_combine(&result, params.precedence);
  hash_combine<int>(&result, params.associativity);
  hash_combine(&result, params.has_precedence);
  hash_combine(&result, params.has_associativity);
  hash_combine(&result, params.is_token);
  hash_combine(&result, params.is_string);
  hash_combine(&result, params.is_active);
  hash_combine(&result, params.is_main_token);
  return result;
}

rule_ptr Metadata::copy() const {
  return make_shared<Metadata>(rule->copy(), params);
}

std::string Metadata::to_string() const {
  if (params.has_precedence) {
    return "(metadata prec:" + std::to_string(params.precedence) + " " +
           rule->to_string() + ")";
  } else {
    return "(metadata " + rule->to_string() + ")";
  }
}

void Metadata::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
