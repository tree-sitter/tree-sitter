#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/item.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace build_tables {

using std::set;
using std::vector;
using std::pair;
using rules::Symbol;
using rules::rule_ptr;

const ParseItemSet item_set_closure(const ParseItem &starting_item,
                                    const set<Symbol> &starting_lookahead_symbols,
                                    const SyntaxGrammar &grammar) {
  ParseItemSet result;
  vector<pair<ParseItem, set<Symbol>>> items_to_process;
  items_to_process.push_back({ starting_item, starting_lookahead_symbols });

  while (!items_to_process.empty()) {
    ParseItem item = items_to_process.back().first;
    set<Symbol> new_lookahead_symbols = items_to_process.back().second;
    items_to_process.pop_back();

    set<Symbol> &lookahead_symbols = result[item];
    size_t previous_size = lookahead_symbols.size();
    lookahead_symbols.insert(new_lookahead_symbols.begin(),
                             new_lookahead_symbols.end());
    if (lookahead_symbols.size() == previous_size)
      continue;

    const Production &item_production = grammar.productions(item.lhs)[item.production_index];
    if (item_production.size() <= item.consumed_symbol_count)
      continue;

    Symbol symbol = item_production.symbol_at(item.consumed_symbol_count);
    if (symbol.is_token() || symbol.is_built_in())
      continue;

    set<Symbol> next_lookahead_symbols;
    if (item.consumed_symbol_count + 1 >= item_production.size()) {
      next_lookahead_symbols = lookahead_symbols;
    } else {
      vector<Symbol> symbols_to_process({ item_production.symbol_at(item.consumed_symbol_count + 1) });

      while (!symbols_to_process.empty()) {
        Symbol following_symbol = symbols_to_process.back();
        symbols_to_process.pop_back();
        if (!next_lookahead_symbols.insert(following_symbol).second)
          continue;

        for (const auto &production : grammar.productions(following_symbol))
          symbols_to_process.push_back(production.symbol_at(0));
      }
    }

    size_t i = 0;
    for (const Production &production : grammar.productions(symbol)) {
      items_to_process.push_back({
        ParseItem(symbol, i, production.rule_id_at(0), 0),
        next_lookahead_symbols
      });
      i++;
    }
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
