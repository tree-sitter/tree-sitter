#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using std::pair;
using std::shared_ptr;
using std::make_shared;
using rules::Symbol;

ParseItemSet item_set_closure(const ParseItemSet &input_item_set,
                              const SyntaxGrammar &grammar) {
  ParseItemSet result;

  // An item set's closure is defined recursively. Use an explicit stack to
  // store the recursively-added items.
  vector<pair<ParseItem, LookaheadSet>> items_to_process(input_item_set.begin(),
                                                         input_item_set.end());
  while (!items_to_process.empty()) {
    ParseItem item = items_to_process.back().first;
    LookaheadSet lookahead_symbols = items_to_process.back().second;
    items_to_process.pop_back();

    // Add the parse-item and lookahead symbols to the item set.
    // If they were already present, skip to the next item.
    if (!result[item].insert_all(lookahead_symbols))
      continue;

    // If the item is at the end of its production, skip to the next item.
    const Production &item_production =
      grammar.productions(item.lhs())[item.production_index];
    if (item.step_index == item_production.size())
      continue;

    // If the next symbol in the production is not a non-terminal, skip to the
    // next item.
    Symbol next_symbol = item_production[item.step_index].symbol;
    if (next_symbol.is_token || next_symbol.is_built_in())
      continue;

    // If the next symbol is the last symbol in the item's production, then the
    // lookahead symbols for the new items are the same as for the current item.
    // Otherwise, compute the FOLLOW-SET of the symbol in this production. This
    // is defined recursively as well, so use another queue to store the
    // recursively-added follow symbols.
    LookaheadSet next_lookahead_symbols;
    size_t next_step = item.step_index + 1;
    if (next_step == item_production.size()) {
      next_lookahead_symbols = lookahead_symbols;
    } else {
      vector<Symbol> symbols_to_process({ item_production[next_step].symbol });
      while (!symbols_to_process.empty()) {
        Symbol following_symbol = symbols_to_process.back();
        symbols_to_process.pop_back();

        if (!next_lookahead_symbols.insert(following_symbol))
          continue;

        for (const auto &production : grammar.productions(following_symbol))
          if (!production.empty())
            symbols_to_process.push_back(production[0].symbol);
      }
    }

    // Add each of the next symbol's productions to be processed recursively.
    size_t i = 0;
    for (const Production &production : grammar.productions(next_symbol)) {
      if (!production.empty())
        items_to_process.push_back({
          ParseItem(next_symbol, i, 0, production[0].rule_id),
          next_lookahead_symbols,
        });
      i++;
    }
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
