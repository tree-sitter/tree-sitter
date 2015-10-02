#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/extract_choices.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/built_in_symbols.h"
#include <string>
#include <algorithm>

namespace tree_sitter {
namespace prepare_grammar {

using std::find;
using std::string;
using std::vector;

class FlattenRule : public rules::RuleFn<void> {
 public:
  bool has_pending_precedence;
  int pending_precedence;
  vector<int> precedence_stack;
  bool has_pending_associativity;
  Associativity pending_associativity;
  vector<Associativity> associativity_stack;
  Production production;

  FlattenRule()
      : has_pending_precedence(false),
        pending_precedence(0),
        has_pending_associativity(false),
        pending_associativity(AssociativityNone) {}

  void apply_to(const rules::Symbol *sym) {
    production.push_back(
      ProductionStep(*sym, current_precedence(), current_associativity()));

    if (has_pending_precedence) {
      precedence_stack.push_back(pending_precedence);
      has_pending_precedence = false;
    }
    if (has_pending_associativity) {
      associativity_stack.push_back(pending_associativity);
      has_pending_associativity = false;
    }
  }

  void apply_to(const rules::Metadata *metadata) {
    int precedence = metadata->value_for(rules::PRECEDENCE);
    int associativity = metadata->value_for(rules::ASSOCIATIVITY);

    if (precedence != 0) {
      pending_precedence = precedence;
      has_pending_precedence = true;
    }

    if (associativity != 0) {
      pending_associativity = static_cast<Associativity>(associativity);
      has_pending_associativity = true;
    }

    apply(metadata->rule);

    if (precedence != 0)
      precedence_stack.pop_back();

    if (associativity != 0)
      associativity_stack.pop_back();
  }

  void apply_to(const rules::Seq *seq) {
    apply(seq->left);
    apply(seq->right);
  }

 private:
  int current_precedence() {
    if (precedence_stack.empty())
      return 0;
    else
      return precedence_stack.back();
  }

  Associativity current_associativity() {
    if (associativity_stack.empty())
      return AssociativityNone;
    else
      return associativity_stack.back();
  }
};

Production flatten_rule(const rule_ptr &rule) {
  FlattenRule flattener;
  flattener.apply(rule);
  return flattener.production;
}

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
      productions.push_back(flatten_rule(rule_component));
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
