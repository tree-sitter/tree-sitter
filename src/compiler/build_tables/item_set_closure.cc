#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/first_symbols.h"
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

    for (const auto &pair : sym_transitions(item.rule)) {
      const Symbol &symbol = pair.first;
      const rule_ptr &next_rule = pair.second;

      if (symbol.is_token() || symbol.is_built_in())
        continue;

      set<Symbol> next_lookahead_symbols = first_symbols(next_rule, grammar);
      if (rule_can_be_blank(next_rule, grammar))
        next_lookahead_symbols.insert(lookahead_symbols.begin(),
                                      lookahead_symbols.end());

      items_to_process.push_back({ ParseItem(symbol, grammar.rule(symbol), 0),
                                   next_lookahead_symbols });
    }
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
