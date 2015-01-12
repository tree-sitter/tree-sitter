#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::pair;
using std::vector;
using std::set;

InitialSyntaxGrammar::InitialSyntaxGrammar() {}

InitialSyntaxGrammar::InitialSyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : rules(rules), aux_rules(aux_rules) {}

InitialSyntaxGrammar::InitialSyntaxGrammar(const vector<pair<string, rules::rule_ptr>> &rules,
                             const vector<pair<string, rules::rule_ptr>> &aux_rules,
                             const set<rules::Symbol> &ubiquitous_tokens)
    : rules(rules), aux_rules(aux_rules), ubiquitous_tokens(ubiquitous_tokens) {}

const rules::rule_ptr &InitialSyntaxGrammar::rule(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].second
                               : rules[symbol.index].second;
}

const string &InitialSyntaxGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
