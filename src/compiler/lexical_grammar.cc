#include "compiler/lexical_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {

using std::string;
using std::pair;
using std::vector;
using std::set;

LexicalGrammar::LexicalGrammar() {}

LexicalGrammar::LexicalGrammar(
    const vector<pair<string, rules::rule_ptr>> &rules,
    const vector<pair<string, rules::rule_ptr>> &aux_rules)
    : rules(rules), aux_rules(aux_rules) {}

LexicalGrammar::LexicalGrammar(
    const vector<pair<string, rules::rule_ptr>> &rules,
    const vector<pair<string, rules::rule_ptr>> &aux_rules,
    const vector<rules::rule_ptr> &separators)
    : rules(rules), aux_rules(aux_rules), separators(separators) {}

const rules::rule_ptr &LexicalGrammar::rule(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].second
                               : rules[symbol.index].second;
}

const string &LexicalGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

}  // namespace tree_sitter
