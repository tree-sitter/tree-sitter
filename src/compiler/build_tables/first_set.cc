#include "compiler/build_tables/first_set.h"
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

using std::set;
using rules::Symbol;

class FirstSet : public rules::RuleFn<set<Symbol> > {
  const SyntaxGrammar *grammar;
  set<Symbol> visited_symbols;

 public:
  explicit FirstSet(const SyntaxGrammar *grammar) : grammar(grammar) {}

  set<Symbol> apply_to(const Symbol *rule) {
    auto insertion_result = visited_symbols.insert(*rule);
    if (insertion_result.second) {
      return (rule->is_token()) ? set<Symbol>({ *rule })
                                : apply(grammar->rule(*rule));
    } else {
      return set<Symbol>();
    }
  }

  set<Symbol> apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  set<Symbol> apply_to(const rules::Choice *rule) {
    set<Symbol> result;
    for (const auto &el : rule->elements) {
      auto &&next_syms = apply(el);
      result.insert(next_syms.begin(), next_syms.end());
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

set<Symbol> first_set(const rules::rule_ptr &rule, const SyntaxGrammar &grammar) {
  return FirstSet(&grammar).apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
