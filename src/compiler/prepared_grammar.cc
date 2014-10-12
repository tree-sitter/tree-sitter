#include "compiler/prepared_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {

using std::string;
using std::pair;
using std::vector;
using std::set;

const rules::rule_ptr &PreparedGrammar::rule(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].second
                               : rules[symbol.index].second;
}

const string &PreparedGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

PreparedGrammar::PreparedGrammar() {}
SyntaxGrammar::SyntaxGrammar() {}
LexicalGrammar::LexicalGrammar() {}

SyntaxGrammar::SyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : PreparedGrammar(rules, aux_rules) {}

LexicalGrammar::LexicalGrammar(
    const vector<pair<string, rules::rule_ptr>> &rules,
    const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : PreparedGrammar(rules, aux_rules) {}

PreparedGrammar::PreparedGrammar(
    const vector<pair<string, rules::rule_ptr>> &rules,
    const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : rules(rules), aux_rules(aux_rules) {}

SyntaxGrammar::SyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules,
                             const set<rules::Symbol> &ubiquitous_tokens)
    : PreparedGrammar(rules, aux_rules), ubiquitous_tokens(ubiquitous_tokens) {}

LexicalGrammar::LexicalGrammar(
    const vector<pair<string, rules::rule_ptr>> &rules,
    const vector<pair<string, rules::rule_ptr>> &aux_rules,
    const vector<rules::rule_ptr> &separators)
    : PreparedGrammar(rules, aux_rules), separators(separators) {}

}  // namespace tree_sitter
