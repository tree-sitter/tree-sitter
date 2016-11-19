#include "compiler/prepare_grammar/flatten_grammar.h"
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
using std::vector;

class FlattenRule : public rules::RuleFn<void> {
 private:
  vector<int> precedence_stack;
  vector<rules::Associativity> associativity_stack;
  int last_precedence;
  rules::Associativity last_associativity;
  Production production;

  void apply_to(const rules::Symbol *sym) {
    production.push_back(ProductionStep(*sym, precedence_stack.back(),
                                        associativity_stack.back()));
  }

  void apply_to(const rules::Metadata *metadata) {
    if (metadata->params.has_precedence)
      precedence_stack.push_back(metadata->params.precedence);
    if (metadata->params.has_associativity)
      associativity_stack.push_back(metadata->params.associativity);

    apply(metadata->rule);

    if (metadata->params.has_precedence) {
      last_precedence = precedence_stack.back();
      precedence_stack.pop_back();
      production.back().precedence = precedence_stack.back();
    }

    if (metadata->params.has_associativity) {
      last_associativity = associativity_stack.back();
      associativity_stack.pop_back();
      production.back().associativity = associativity_stack.back();
    }
  }

  void apply_to(const rules::Seq *seq) {
    apply(seq->left);
    last_precedence = 0;
    last_associativity = rules::AssociativityNone;
    apply(seq->right);
  }

 public:
  FlattenRule()
      : precedence_stack({ 0 }),
        associativity_stack({ rules::AssociativityNone }),
        last_precedence(0),
        last_associativity(rules::AssociativityNone) {}

  Production flatten(const rule_ptr &rule) {
    apply(rule);
    if (!production.empty()) {
      production.back().precedence = last_precedence;
      production.back().associativity = last_associativity;
    }
    return production;
  }
};

SyntaxVariable flatten_rule(const Variable &variable) {
  vector<Production> productions;

  for (const rule_ptr &rule_component : extract_choices(variable.rule)) {
    Production production = FlattenRule().flatten(rule_component);
    auto end = productions.end();
    if (find(productions.begin(), end, production) == end) {
      productions.push_back(production);
    }
  }

  return SyntaxVariable(variable.name, variable.type, productions);
}

SyntaxGrammar flatten_grammar(const InitialSyntaxGrammar &grammar) {
  SyntaxGrammar result;
  result.expected_conflicts = grammar.expected_conflicts;
  result.extra_tokens = grammar.extra_tokens;

  for (const Variable &variable : grammar.variables) {
    result.variables.push_back(flatten_rule(variable));
  }

  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
