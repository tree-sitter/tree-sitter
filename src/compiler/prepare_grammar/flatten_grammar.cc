#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/extract_choices.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include <string>
#include <algorithm>

namespace tree_sitter {
namespace prepare_grammar {

using std::find;
using std::pair;
using std::string;
using std::vector;
using rules::rule_ptr;

class FlattenRule : public rules::RuleFn<void> {
 public:
  bool has_pending_precedence;
  int pending_precedence;
  vector<int> precedence_stack;
  vector<ProductionEntry> entries;

  FlattenRule() : has_pending_precedence(false), pending_precedence(0) {}

  void apply_to(const rules::Symbol *sym) {
    entries.push_back({ *sym, current_precedence(), 0 });
    if (has_pending_precedence) {
      precedence_stack.push_back(pending_precedence);
      has_pending_precedence = false;
    }
  }

  void apply_to(const rules::Metadata *metadata) {
    int precedence = metadata->value_for(rules::PRECEDENCE);
    if (precedence != 0) {
      pending_precedence = precedence;
      has_pending_precedence = true;
      apply(metadata->rule);
      precedence_stack.pop_back();
    } else {
      apply(metadata->rule);
    }
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
      return *precedence_stack.rbegin();
  }
};

Production flatten_rule(const rule_ptr &rule) {
  FlattenRule flattener;
  flattener.apply(rule);
  return Production(flattener.entries, 0);
}

struct ProductionSlice {
  vector<ProductionEntry>::const_iterator start;
  vector<ProductionEntry>::const_iterator end;
  int end_precedence;

  bool operator==(const ProductionSlice &other) const {
    if (end_precedence != other.end_precedence) return false;
    if (end - start != other.end - other.start) return false;
    for (auto iter1 = start, iter2 = other.start; iter1 != end; ++iter1, ++iter2)
      if (!(iter1->symbol == iter2->symbol) || iter1->precedence != iter2->precedence)
        return false;
    return true;
  }
};

void assign_rule_ids(Production *production, vector<ProductionSlice> *unique_slices) {
  auto &entries = production->entries;
  auto end = entries.end();

  for (auto iter = entries.begin(); iter != end; ++iter) {
    ProductionSlice slice{iter, end, 0};
    auto existing_id = find(unique_slices->cbegin(), unique_slices->cend(), slice);
    if (existing_id == unique_slices->end()) {
      unique_slices->push_back(slice);
      iter->rule_id = unique_slices->size() - 1;
    } else {
      iter->rule_id = existing_id - unique_slices->cbegin();
    }
  }

  ProductionSlice slice{end, end, production->precedence_at(production->size() - 1)};
  auto existing_id = find(unique_slices->cbegin(), unique_slices->cend(), slice);
  if (existing_id == unique_slices->end()) {
    unique_slices->push_back(slice);
    production->end_rule_id = unique_slices->size() - 1;
  } else {
    production->end_rule_id = existing_id - unique_slices->cbegin();
  }
}

SyntaxGrammar flatten_grammar(const InitialSyntaxGrammar &grammar) {
  vector<pair<string, vector<Production>>> rules, aux_rules;

  for (const auto &pair : grammar.rules) {
    vector<Production> productions;
    for (const auto &rule_component : extract_choices(pair.second))
      productions.push_back(flatten_rule(rule_component));
    rules.push_back({ pair.first, productions });
  }

  for (const auto &pair : grammar.aux_rules) {
    vector<Production> productions;
    for (const auto &rule_component : extract_choices(pair.second))
      productions.push_back(flatten_rule(rule_component));
    aux_rules.push_back({ pair.first, productions });
  }

  if (rules.empty()) {
    rules.push_back({
      "START",
      { Production({ {rules::Symbol(0, rules::SymbolOptionToken), 0, 0} }, 0) }
    });
  }

  vector<ProductionSlice> unique_slices;
  for (auto &pair : rules)
    for (Production &production : pair.second)
      assign_rule_ids(&production, &unique_slices);
  for (auto &pair : aux_rules)
    for (Production &production : pair.second)
      assign_rule_ids(&production, &unique_slices);

  return SyntaxGrammar(rules, aux_rules, grammar.ubiquitous_tokens);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
