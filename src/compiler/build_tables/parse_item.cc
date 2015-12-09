#include "compiler/build_tables/parse_item.h"
#include <string>
#include "compiler/syntax_grammar.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::pair;
using std::string;
using std::to_string;
using std::hash;
using rules::Symbol;

ParseItem::ParseItem(const Symbol &lhs, const Production &production,
                     unsigned int step_index)
    : variable_index(lhs.index),
      production(&production),
      step_index(step_index) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return ((variable_index == other.variable_index) &&
          (step_index == other.step_index) &&
          (production == other.production));
}

bool ParseItem::operator<(const ParseItem &other) const {
  if (variable_index < other.variable_index)
    return true;
  if (variable_index > other.variable_index)
    return false;
  if (step_index < other.step_index)
    return true;
  if (step_index > other.step_index)
    return false;
  return production < other.production;
}

Symbol ParseItem::lhs() const {
  return Symbol(variable_index);
}

ParseItem::CompletionStatus ParseItem::completion_status() const {
  CompletionStatus result = { false, 0, rules::AssociativityNone };
  if (step_index == production->size()) {
    result.is_done = true;
    if (step_index > 0) {
      const ProductionStep &last_step = production->at(step_index - 1);
      result.precedence = last_step.precedence;
      result.associativity = last_step.associativity;
    }
  }
  return result;
}

int ParseItem::precedence() const {
  if (production->empty())
    return 0;
  else if (completion_status().is_done)
    return production->back().precedence;
  else
    return production->at(step_index).precedence;
}

rules::Associativity ParseItem::associativity() const {
  if (production->empty())
    return rules::AssociativityNone;
  else if (completion_status().is_done)
    return production->back().associativity;
  else
    return production->at(step_index).associativity;
}

size_t ParseItem::Hash::operator()(const ParseItem &item) const {
  size_t result = hash<int>()(item.variable_index);
  result ^= hash<unsigned int>()(item.step_index);
  result ^= hash<void *>()((void *)item.production);
  return result;
}

ParseItemSet::ParseItemSet() {}

ParseItemSet::ParseItemSet(const map<ParseItem, LookaheadSet> &entries)
    : entries(entries) {}

bool ParseItemSet::operator==(const ParseItemSet &other) const {
  return entries == other.entries;
}

size_t ParseItemSet::Hash::operator()(const ParseItemSet &item_set) const {
  size_t result = hash<size_t>()(item_set.entries.size());
  for (auto &pair : item_set.entries) {
    const ParseItem &item = pair.first;
    result ^= ParseItem::Hash()(item);

    const LookaheadSet &lookahead_set = pair.second;
    result ^= hash<size_t>()(lookahead_set.entries->size());
    for (auto &symbol : *pair.second.entries)
      result ^= hash<tree_sitter::rules::Symbol>()(symbol);
  }
  return result;
}

ParseItemSet::TransitionMap ParseItemSet::transitions() const {
  ParseItemSet::TransitionMap result;
  for (const auto &pair : entries) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookahead_symbols = pair.second;
    if (item.step_index == item.production->size())
      continue;

    size_t step = item.step_index + 1;
    Symbol symbol = item.production->at(item.step_index).symbol;
    int precedence = item.production->at(item.step_index).precedence;
    ParseItem new_item(item.lhs(), *item.production, step);

    result[symbol].first.entries[new_item] = lookahead_symbols;
    result[symbol].second.add(precedence);
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
