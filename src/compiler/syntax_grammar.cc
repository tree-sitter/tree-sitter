#include "compiler/syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {

using std::string;

const rules::rule_ptr &SyntaxGrammar::rule(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].second
                               : rules[symbol.index].second;
}

const string &SyntaxGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

}  // namespace tree_sitter
