#include <set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::set;
using rules::CharacterSet;
using rules::Symbol;

map<Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set,
                                          const SyntaxGrammar &grammar) {
  map<Symbol, ParseItemSet> result;
  for (const auto &pair : item_set) {
    const ParseItem &item = pair.first;
    const set<Symbol> &lookahead_symbols = pair.second;
    const auto &productions = grammar.productions(item.lhs);
    if (productions.empty())
      continue;

    const Production &production = grammar.productions(item.lhs)[item.production_index];
    if (production.size() <= item.consumed_symbol_count)
      continue;

    const Symbol &symbol = production.symbol_at(item.consumed_symbol_count);
    ParseItem new_item(
      item.lhs,
      item.production_index,
      production.rule_id_at(item.consumed_symbol_count + 1),
      item.consumed_symbol_count + 1
    );

    merge_sym_transition<ParseItemSet>(
      &result,
      { symbol, item_set_closure(new_item, { lookahead_symbols }, grammar) },
      [](ParseItemSet *left, const ParseItemSet *right) {
        for (auto &pair : *right)
          left->operator[](pair.first)
            .insert(pair.second.begin(), pair.second.end());
      });
  }
  return result;
}

map<CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set) {
  map<CharacterSet, LexItemSet> result;
  for (const LexItem &item : item_set) {
    for (auto &transition : char_transitions(item.rule)) {
      LexItem next_item(item.lhs, transition.second);
      merge_char_transition<LexItemSet>(
          &result, { transition.first, LexItemSet({ next_item }) },
          [](LexItemSet *left, const LexItemSet *right) {
            left->insert(right->begin(), right->end());
          });
    }
  }
  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
