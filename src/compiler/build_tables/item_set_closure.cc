#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
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
  vector<pair<ParseItem, LookaheadSet>> items_to_process(
    input_item_set.entries.begin(), input_item_set.entries.end());

  while (!items_to_process.empty()) {
    ParseItem item = items_to_process.back().first;
    LookaheadSet lookahead_symbols = items_to_process.back().second;
    items_to_process.pop_back();

    // Add the parse-item and lookahead symbols to the item set.
    // If they were already present, skip to the next item.
    if (!result.entries[item].insert_all(lookahead_symbols))
      continue;

    // If the item is at the end of its production, skip to the next item.
    if (item.step_index == item.production->size())
      continue;

    // If the next symbol in the production is not a non-terminal, skip to the
    // next item.
    Symbol next_symbol = item.production->at(item.step_index).symbol;
    if (next_symbol.is_token || next_symbol.is_built_in())
      continue;

    // If the next symbol is the last symbol in the item's production, then the
    // lookahead symbols for the new items are the same as for the current item.
    // Otherwise, compute the FOLLOW-SET of the symbol in this production. This
    // is defined recursively as well, so use another queue to store the
    // recursively-added follow symbols.
    LookaheadSet next_lookahead_symbols;
    size_t next_step = item.step_index + 1;
    if (next_step == item.production->size()) {
      next_lookahead_symbols = lookahead_symbols;
    } else {
      vector<Symbol> symbols_to_process(
        { item.production->at(next_step).symbol });
      while (!symbols_to_process.empty()) {
        Symbol symbol = symbols_to_process.back();
        symbols_to_process.pop_back();

        if (!next_lookahead_symbols.insert(symbol))
          continue;

        for (const Production &production : grammar.productions(symbol))
          if (!production.empty())
            symbols_to_process.push_back(production[0].symbol);
      }
    }

    // Add each of the next symbol's productions to be processed recursively.
    for (const Production &production : grammar.productions(next_symbol))
      items_to_process.push_back({
        ParseItem(next_symbol, production, 0), next_lookahead_symbols,
      });
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
