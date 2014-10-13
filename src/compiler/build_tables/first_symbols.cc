#include "compiler/build_tables/first_symbols.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/visitor.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::set;
using rules::Symbol;

class FirstSymbols : public rules::RuleFn<set<Symbol>> {
  const SyntaxGrammar *grammar;
  set<Symbol> visited_symbols;

 public:
  explicit FirstSymbols(const SyntaxGrammar *grammar) : grammar(grammar) {}

 private:
  set<Symbol> apply_to(const Symbol *rule) {
    auto insertion_result = visited_symbols.insert(*rule);
    if (!insertion_result.second)
      return set<Symbol>();

    set<Symbol> result({ *rule });
    if (!rule->is_token()) {
      set<Symbol> &&symbols = apply(grammar->rule(*rule));
      result.insert(symbols.begin(), symbols.end());
    }

    return result;
  }

  set<Symbol> apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  set<Symbol> apply_to(const rules::Choice *rule) {
    set<Symbol> result;
    for (const auto &element : rule->elements) {
      auto &&element_symbols = apply(element);
      result.insert(element_symbols.begin(), element_symbols.end());
    }
    return result;
  }

  set<Symbol> apply_to(const rules::Seq *rule) {
    auto &&result = apply(rule->left);
    if (rule_can_be_blank(rule->left, *grammar)) {
      auto &&right_symbols = apply(rule->right);
      result.insert(right_symbols.begin(), right_symbols.end());
    }
    return result;
  }
};

set<Symbol> first_symbols(const rules::rule_ptr &rule,
                          const SyntaxGrammar &grammar) {
  return FirstSymbols(&grammar).apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
