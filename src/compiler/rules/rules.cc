#include <vector>
#include <map>
#include <set>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/rule.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {

using std::make_shared;
using std::string;
using std::set;
using std::vector;
using std::map;

static rule_ptr metadata(rule_ptr rule, map<rules::MetadataKey, int> values) {
  return std::make_shared<rules::Metadata>(rule, values);
}

rule_ptr blank() {
  return rules::Blank::build();
}

rule_ptr choice(const vector<rule_ptr> &rules) {
  return rules::Choice::build(rules);
}

rule_ptr repeat(const rule_ptr &content) {
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

rule_ptr err(const rule_ptr &rule) {
  return choice({ rule, rules::ERROR().copy() });
}

rule_ptr prec(int precedence, const rule_ptr &rule, Associativity associativity) {
  return metadata(rule, { { rules::PRECEDENCE, precedence },
                          { rules::ASSOCIATIVITY, associativity } });
}

rule_ptr prec(int precedence, const rule_ptr &rule) {
  return prec(precedence, rule, AssociativityLeft);
}

rule_ptr token(const rule_ptr &rule) {
  return metadata(rule, { { rules::IS_TOKEN, 1 } });
}

}  // namespace tree_sitter
