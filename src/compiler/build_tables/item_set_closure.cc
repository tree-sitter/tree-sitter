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

void item_set_closure(ParseItemSet *item_set, const SyntaxGrammar &grammar) {
  vector<pair<ParseItem, set<Symbol>>> items_to_process;
  items_to_process.insert(items_to_process.end(), item_set->begin(),
                          item_set->end());
  item_set->clear();

  while (!items_to_process.empty()) {
    ParseItem item = items_to_process.back().first;
    set<Symbol> new_lookahead_symbols = items_to_process.back().second;
    items_to_process.pop_back();

    set<Symbol> &lookahead_symbols = item_set->operator[](item);
    size_t previous_size = lookahead_symbols.size();
    lookahead_symbols.insert(new_lookahead_symbols.begin(),
                             new_lookahead_symbols.end());
    if (lookahead_symbols.size() == previous_size)
      continue;

    const Production &item_production =
      grammar.productions(item.lhs())[item.production_index];

    if (item.step_index == item_production.size())
      continue;

    Symbol symbol = item_production[item.step_index].symbol;

    if (symbol.is_token || symbol.is_built_in())
      continue;

    set<Symbol> next_lookahead_symbols;
    unsigned int next_step = item.step_index + 1;
    if (next_step == item_production.size()) {
      next_lookahead_symbols = lookahead_symbols;
    } else {
      vector<Symbol> symbols_to_process({ item_production[next_step].symbol });

      while (!symbols_to_process.empty()) {
        Symbol following_symbol = symbols_to_process.back();
        symbols_to_process.pop_back();
        if (!next_lookahead_symbols.insert(following_symbol).second)
          continue;

        for (const auto &production : grammar.productions(following_symbol))
          if (!production.empty())
            symbols_to_process.push_back(production[0].symbol);
      }
    }

    size_t i = 0;
    for (const Production &production : grammar.productions(symbol)) {
      if (!production.empty())
        items_to_process.push_back(
          { ParseItem(symbol, i, 0, production[0].rule_id),
            next_lookahead_symbols });
      i++;
    }
  }
}

}  // namespace build_tables
}  // namespace tree_sitter
