#include "compiler/syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {

using std::string;
using std::pair;
using std::vector;
using std::set;

SyntaxGrammar::SyntaxGrammar() {}

SyntaxGrammar::SyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : rules(rules), aux_rules(aux_rules) {}

SyntaxGrammar::SyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules,
                             const set<rules::Symbol> &ubiquitous_tokens,
                             const set<set<rules::Symbol>> &expected_conflicts)
    : rules(rules), aux_rules(aux_rules),
      ubiquitous_tokens(ubiquitous_tokens), expected_conflicts(expected_conflicts) {}

const rules::rule_ptr &SyntaxGrammar::rule(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].second
                               : rules[symbol.index].second;
}

const string &SyntaxGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

}  // namespace tree_sitter
