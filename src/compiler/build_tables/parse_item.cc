#include "compiler/build_tables/parse_item.h"
#include <string>
#include "compiler/syntax_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::pair;
using std::string;
using std::to_string;
using rules::Symbol;
using util::hash_combine;

ParseItem::ParseItem() : variable_index(-1), production(nullptr), step_index(0) {}

ParseItem::ParseItem(const Symbol &lhs, const Production &production,
                     unsigned int step_index)
    : variable_index(lhs.index),
      production(&production),
      step_index(step_index) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return ((variable_index == other.variable_index) &&
          (step_index == other.step_index) && (production == other.production));
}

bool ParseItem::operator<(const ParseItem &other) const {
  if (step_index < other.step_index)
    return true;
  if (step_index > other.step_index)
    return false;
  if (variable_index < other.variable_index)
    return true;
  if (variable_index > other.variable_index)
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

Symbol ParseItem::next_symbol() const {
  if (step_index >= production->size())
    return rules::NONE();
  else
    return production->at(step_index).symbol;
}

rules::Associativity ParseItem::associativity() const {
  if (production->empty())
    return rules::AssociativityNone;
  else if (completion_status().is_done)
    return production->back().associativity;
  else
    return production->at(step_index).associativity;
}

ParseItemSet::ParseItemSet() {}

ParseItemSet::ParseItemSet(const map<ParseItem, LookaheadSet> &entries)
    : entries(entries) {}

bool ParseItemSet::operator==(const ParseItemSet &other) const {
  return entries == other.entries;
}

size_t ParseItemSet::unfinished_item_signature() const {
  size_t result = 0;
  ParseItem previous_item;
  for (auto &pair : entries) {
    const ParseItem &item = pair.first;
    if (item.step_index < item.production->size()) {
      if (item.variable_index != previous_item.variable_index &&
          item.step_index != previous_item.step_index) {
        hash_combine(&result, item.variable_index);
        hash_combine(&result, item.step_index);
        previous_item = item;
      }
    }
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

void ParseItemSet::add(const ParseItemSet &other) {
  for (const auto &pair : other.entries)
    entries[pair.first].insert_all(pair.second);
}

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::build_tables::ParseItem;
using tree_sitter::build_tables::ParseItemSet;
using tree_sitter::util::hash_combine;

template <>
struct hash<ParseItem> {
  size_t operator()(const ParseItem &item) const {
    size_t result = 0;
    hash_combine(&result, item.variable_index);
    hash_combine(&result, item.step_index);
    hash_combine(&result, item.production);
    return result;
  }
};

size_t hash<ParseItemSet>::operator()(const ParseItemSet &item_set) const {
  size_t result = 0;
  hash_combine(&result, item_set.entries.size());
  for (auto &pair : item_set.entries) {
    const ParseItem &item = pair.first;
    const auto &lookahead_set = pair.second;

    hash_combine(&result, item);
    hash_combine(&result, lookahead_set.entries->size());
    for (auto index : *pair.second.entries)
      hash_combine(&result, index);
  }
  return result;
}

}  // namespace std
