#include <vector>
#include <map>
#include <set>
#include <string>
#include "compiler/rule.h"
#include "compiler/rules.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/external_token.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {

using std::make_shared;
using std::string;
using std::set;
using std::vector;
using std::map;
using rules::MetadataParams;

static rule_ptr metadata(rule_ptr rule, MetadataParams params) {
  return std::make_shared<rules::Metadata>(rule, params);
}

rule_ptr blank() {
  return rules::Blank::build();
}

rule_ptr choice(const vector<rule_ptr> &rules) {
  return rules::Choice::build(rules);
}

rule_ptr repeat(const rule_ptr &content) {
  return choice({ repeat1(content), blank() });
}

rule_ptr repeat1(const rule_ptr &content) {
  return rules::Repeat::build(content);
}

rule_ptr seq(const vector<rule_ptr> &rules) {
  return rules::Seq::build(rules);
}

rule_ptr sym(const string &name) {
  return make_shared<rules::NamedSymbol>(name);
}

rule_ptr pattern(const string &value) {
  return make_shared<rules::Pattern>(value);
}

rule_ptr str(const string &value) {
  return make_shared<rules::String>(value);
}

rule_ptr prec_left(const rule_ptr &rule) {
  MetadataParams params;
  params.has_associativity = true;
  params.associativity = rules::AssociativityLeft;
  return metadata(rule, params);
}

rule_ptr prec_left(int precedence, const rule_ptr &rule) {
  MetadataParams params;
  params.has_associativity = true;
  params.associativity = rules::AssociativityLeft;
  params.has_precedence = true;
  params.precedence = precedence;
  return metadata(rule, params);
}

rule_ptr prec_right(const rule_ptr &rule) {
  MetadataParams params;
  params.has_associativity = true;
  params.associativity = rules::AssociativityRight;
  return metadata(rule, params);
}

rule_ptr prec_right(int precedence, const rule_ptr &rule) {
  MetadataParams params;
  params.has_associativity = true;
  params.associativity = rules::AssociativityRight;
  params.has_precedence = true;
  params.precedence = precedence;
  return metadata(rule, params);
}

rule_ptr prec(int precedence, const rule_ptr &rule) {
  MetadataParams params;
  params.has_precedence = true;
  params.precedence = precedence;
  return metadata(rule, params);
}

rule_ptr token(const rule_ptr &rule) {
  MetadataParams params;
  params.is_token = true;
  return metadata(rule, params);
}

rule_ptr external_token(const string &name) {
  return rules::ExternalToken::build(name);
}

}  // namespace tree_sitter
