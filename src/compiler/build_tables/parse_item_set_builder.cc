#include "compiler/build_tables/parse_item_set_builder.h"
#include <set>
#include <vector>
#include <utility>
#include "compiler/syntax_grammar.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using std::set;
using std::map;
using std::get;
using std::tuple;
using std::make_tuple;
using std::shared_ptr;
using std::make_shared;
using rules::Symbol;
using rules::NONE;

static map<Symbol, LookaheadSet> build_first_sets(const SyntaxGrammar &grammar) {
  map<Symbol, LookaheadSet> result;
  vector<Symbol> symbol_stack;
  set<Symbol> processed_symbols;

  for (size_t i = 0; i < grammar.variables.size(); i++) {
    Symbol symbol(i);
    LookaheadSet first_set;

    processed_symbols.clear();
    symbol_stack.clear();
    symbol_stack.push_back(symbol);
    while (!symbol_stack.empty()) {
      Symbol current_symbol = symbol_stack.back();
      symbol_stack.pop_back();
      if (current_symbol.is_token) {
        first_set.insert(current_symbol);
      } else if (processed_symbols.insert(current_symbol).second) {
        for (const Production &production : grammar.productions(current_symbol)) {
          if (!production.empty()) {
            symbol_stack.push_back(production[0].symbol);
          }
        }
      }
    }

    result.insert({symbol, first_set});
  }

  return result;
}

ParseItemSetBuilder::ParseItemSetBuilder(const SyntaxGrammar &grammar) :
    grammar{&grammar}, first_sets{build_first_sets(grammar)} {
}

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  items_to_process.clear();
  for (const auto &entry : item_set->entries) {
    items_to_process.push_back(make_tuple(entry.first, entry.second, true));
  }

  while (!items_to_process.empty()) {
    ParseItem item = get<0>(items_to_process.back());
    LookaheadSet lookahead_symbols = get<1>(items_to_process.back());
    bool from_original_set = get<2>(items_to_process.back());
    items_to_process.pop_back();

    // Add the parse-item and lookahead symbols to the item set.
    // If they were already present, skip to the next item.
    if (!from_original_set && !item_set->entries[item].insert_all(lookahead_symbols))
      continue;

    // If the next symbol in the production is not a non-terminal, skip to the
    // next item.
    Symbol next_symbol = item.next_symbol();
    if (next_symbol == NONE() || next_symbol.is_token ||
        next_symbol.is_built_in())
      continue;

    // If the next symbol is the last symbol in the item's production, then the
    // lookahead symbols for the new items are the same as for the current item.
    // Otherwise, they are the FOLLOW set of the symbol in this production.
    LookaheadSet next_lookahead_symbols;
    size_t next_step = item.step_index + 1;
    if (next_step == item.production->size()) {
      next_lookahead_symbols = lookahead_symbols;
    } else {
      Symbol symbol_after_next = item.production->at(next_step).symbol;
      if (symbol_after_next.is_token) {
        next_lookahead_symbols.insert(symbol_after_next);
      } else {
        next_lookahead_symbols = first_sets.find(symbol_after_next)->second;
      }
    }

    // Add each of the next symbol's productions to be processed recursively.
    for (const Production &production : grammar->productions(next_symbol))
      items_to_process.push_back(make_tuple(
        ParseItem(next_symbol, production, 0),
        next_lookahead_symbols,
        false
      ));
  }
}

}  // namespace build_tables
}  // namespace tree_sitter
