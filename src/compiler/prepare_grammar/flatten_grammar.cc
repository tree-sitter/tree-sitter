#include "compiler/prepare_grammar/flatten_grammar.h"
#include <string>
#include <vector>
#include <algorithm>
#include "compiler/prepare_grammar/extract_choices.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::find;
using std::string;
using std::vector;

class FlattenRule : public rules::RuleFn<void> {
 private:
  vector<int> precedence_stack;
  vector<rules::Associativity> associativity_stack;
  Production production;

  void apply_to(const rules::Symbol *sym) {
    production.push_back(ProductionStep(*sym, precedence_stack.back(),
                                        associativity_stack.back()));
  }

  void apply_to(const rules::Metadata *metadata) {
    auto precedence = metadata->value_for(rules::PRECEDENCE);
    auto associativity = metadata->value_for(rules::ASSOCIATIVITY);

    if (precedence.second)
      precedence_stack.push_back(precedence.first);
    if (associativity.second)
      associativity_stack.push_back(
        static_cast<rules::Associativity>(associativity.first));

    apply(metadata->rule);

    if (precedence.second) {
      precedence_stack.pop_back();
      production.back().precedence = precedence_stack.back();
    }

    if (associativity.second) {
      associativity_stack.pop_back();
      production.back().associativity = associativity_stack.back();
    }
  }

  void apply_to(const rules::Seq *seq) {
    apply(seq->left);
    apply(seq->right);
  }

 public:
  FlattenRule()
      : precedence_stack({ 0 }),
        associativity_stack({ rules::AssociativityNone }) {}

  Production flatten(const rule_ptr &rule) {
    apply(rule);
    size_t size = production.size();
    if (size > 1) {
      production[size - 1].precedence = production[size - 2].precedence;
      production[size - 1].associativity = production[size - 2].associativity;
    }
    return production;
  }
};

SyntaxGrammar flatten_grammar(const InitialSyntaxGrammar &grammar) {
  SyntaxGrammar result;
  result.expected_conflicts = grammar.expected_conflicts;
  result.ubiquitous_tokens = grammar.ubiquitous_tokens;

  for (const Variable &variable : grammar.variables) {
    vector<Production> productions;
    for (const rule_ptr &rule_component : extract_choices(variable.rule)) {
      Production production = FlattenRule().flatten(rule_component);
      if (std::find(productions.begin(), productions.end(), production) == productions.end())
        productions.push_back(production);
    }
    result.variables.push_back(
      SyntaxVariable(variable.name, variable.type, productions));
  }

  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
