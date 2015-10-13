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
  vector<Associativity> associativity_stack;
  Production production;

  void apply_to(const rules::Symbol *sym) {
    production.push_back(ProductionStep(*sym, precedence_stack.back(),
                                        associativity_stack.back()));
  }

  void apply_to(const rules::Metadata *metadata) {
    int precedence = metadata->value_for(rules::PRECEDENCE);
    int associativity = metadata->value_for(rules::ASSOCIATIVITY);

    if (precedence != 0)
      precedence_stack.push_back(precedence);
    if (associativity != 0)
      associativity_stack.push_back(static_cast<Associativity>(associativity));

    apply(metadata->rule);

    if (precedence != 0) {
      precedence_stack.pop_back();
      production.back().precedence = precedence_stack.back();
    }

    if (associativity != 0) {
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
      : precedence_stack({ 0 }), associativity_stack({ AssociativityNone }) {}

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

struct ProductionSlice {
  vector<ProductionStep>::const_iterator start;
  vector<ProductionStep>::const_iterator end;

  bool operator==(const ProductionSlice &other) const {
    if (end - start != other.end - other.start)
      return false;
    for (auto iter1 = start, iter2 = other.start; iter1 != end; ++iter1, ++iter2)
      if (!(iter1->symbol == iter2->symbol &&
            iter1->precedence == iter2->precedence &&
            iter1->associativity == iter2->associativity))
        return false;
    return true;
  }
};

void assign_rule_ids(Production *production,
                     vector<ProductionSlice> *unique_slices) {
  auto end = production->end();

  for (auto iter = production->begin(); iter != end; ++iter) {
    ProductionSlice slice{ iter, end };
    auto existing_id =
      find(unique_slices->cbegin(), unique_slices->cend(), slice);
    if (existing_id == unique_slices->end()) {
      unique_slices->push_back(slice);
      iter->rule_id = unique_slices->size();
    } else {
      iter->rule_id = existing_id - unique_slices->cbegin() + 1;
    }
  }
}

SyntaxGrammar flatten_grammar(const InitialSyntaxGrammar &grammar) {
  SyntaxGrammar result;
  result.expected_conflicts = grammar.expected_conflicts;
  result.ubiquitous_tokens = grammar.ubiquitous_tokens;

  for (const Variable &variable : grammar.variables) {
    vector<Production> productions;
    for (const rule_ptr &rule_component : extract_choices(variable.rule))
      productions.push_back(FlattenRule().flatten(rule_component));
    result.variables.push_back(
      SyntaxVariable(variable.name, variable.type, productions));
  }

  vector<ProductionSlice> unique_slices;
  for (SyntaxVariable &variable : result.variables)
    for (Production &production : variable.productions)
      assign_rule_ids(&production, &unique_slices);

  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
