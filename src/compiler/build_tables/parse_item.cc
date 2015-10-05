#include "compiler/build_tables/parse_item.h"
#include <string>
#include "compiler/syntax_grammar.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::string;
using std::to_string;
using std::hash;
using rules::Symbol;

ParseItem::ParseItem(const Symbol &lhs, unsigned int production_index,
                     unsigned int step_index, int rule_id)
    : variable_index(lhs.index),
      production_index(production_index),
      step_index(step_index),
      rule_id(rule_id) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (variable_index == other.variable_index) &&
         (rule_id == other.rule_id) && (step_index == other.step_index);
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
  return rule_id < other.rule_id;
}

Symbol ParseItem::lhs() const {
  return Symbol(variable_index);
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
    result ^= hash<unsigned int>()(item.variable_index) ^
              hash<int>()(item.rule_id) ^ hash<unsigned int>()(item.step_index);

    const LookaheadSet &lookahead_set = pair.second;
    result ^= hash<size_t>()(lookahead_set.entries->size());
    for (auto &symbol : *pair.second.entries) {
      result ^= hash<tree_sitter::rules::Symbol>()(symbol);
    }
  }
  return result;
}

map<Symbol, ParseItemSet> ParseItemSet::transitions(
  const SyntaxGrammar &grammar) const {
  map<Symbol, ParseItemSet> result;
  for (const auto &pair : entries) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookahead_symbols = pair.second;
    const Production &production =
      grammar.productions(item.lhs())[item.production_index];
    if (item.step_index == production.size())
      continue;

    size_t step = item.step_index + 1;
    Symbol symbol = production[item.step_index].symbol;
    int rule_id = step < production.size() ? production[step].rule_id : 0;
    ParseItem new_item(item.lhs(), item.production_index, step, rule_id);

    result[symbol].entries[new_item] = lookahead_symbols;
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
