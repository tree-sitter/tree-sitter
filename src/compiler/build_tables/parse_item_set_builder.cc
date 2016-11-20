#include "compiler/build_tables/parse_item_set_builder.h"
#include <set>
#include <vector>
#include <utility>
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using std::set;
using std::map;
using std::get;
using std::pair;
using std::tuple;
using std::make_tuple;
using std::shared_ptr;
using std::make_shared;
using rules::Symbol;
using rules::NONE;

static Symbol::Index PROPAGATE = -5;

ParseItemSetBuilder::ParseItemSetBuilder(const SyntaxGrammar &grammar,
                                         const LexicalGrammar &lexical_grammar) {
  vector<pair<ParseItem, LookaheadSet>> items_to_process;
  vector<Symbol> symbols_to_process;
  set<Symbol::Index> processed_non_terminals;

  for (size_t i = 0, n = lexical_grammar.variables.size(); i < n; i++) {
    Symbol symbol(i, true);
    first_sets.insert({symbol, LookaheadSet({ static_cast<Symbol::Index>(i) })});
  }

  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol(i);
    LookaheadSet first_set;

    processed_non_terminals.clear();
    symbols_to_process.clear();
    symbols_to_process.push_back(symbol);
    while (!symbols_to_process.empty()) {
      Symbol current_symbol = symbols_to_process.back();
      symbols_to_process.pop_back();

      if (current_symbol.is_token) {
        first_set.insert(current_symbol.index);
      } else if (processed_non_terminals.insert(current_symbol.index).second) {
        for (const Production &production : grammar.productions(current_symbol)) {
          if (!production.empty()) {
            symbols_to_process.push_back(production[0].symbol);
          }
        }
      }
    }

    first_sets.insert({symbol, first_set});
  }

  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol(i);
    ParseItemSet item_set;

    items_to_process.clear();
    for (const Production &production : grammar.productions(symbol)) {
      items_to_process.push_back({
        ParseItem(symbol, production, 0),
        LookaheadSet({ PROPAGATE }),
      });
    }

    while (!items_to_process.empty()) {
      ParseItem item = items_to_process.back().first;
      LookaheadSet lookaheads = items_to_process.back().second;
      items_to_process.pop_back();

      if (item_set.entries[item].insert_all(lookaheads)) {
        Symbol next_symbol = item.next_symbol();
        if (next_symbol.is_built_in() || next_symbol.is_token)
          continue;

        LookaheadSet next_lookaheads;
        size_t next_step = item.step_index + 1;
        if (next_step == item.production->size()) {
          next_lookaheads = lookaheads;
        } else {
          Symbol symbol_after_next = item.production->at(next_step).symbol;
          next_lookaheads = first_sets.find(symbol_after_next)->second;
        }

        for (const Production &production : grammar.productions(next_symbol)) {
          items_to_process.push_back({
            ParseItem(next_symbol, production, 0),
            next_lookaheads,
          });
        }
      }
    }

    cached_item_sets.insert({symbol.index, item_set});
  }
}

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  item_set_buffer.clear();
  for (const auto &pair : item_set->entries) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookaheads = pair.second;

    const Symbol &next_symbol = item.next_symbol();
    if (!next_symbol.is_token && !next_symbol.is_built_in()) {
      LookaheadSet next_lookaheads;
      size_t next_step = item.step_index + 1;
      if (next_step == item.production->size()) {
        next_lookaheads = lookaheads;
      } else {
        Symbol symbol_after_next = item.production->at(next_step).symbol;
        next_lookaheads = first_sets.find(symbol_after_next)->second;
      }

      for (const auto &cached_pair : cached_item_sets[next_symbol.index].entries) {
        const ParseItem &cached_item = cached_pair.first;
        const LookaheadSet &cached_lookaheads = cached_pair.second;

        LookaheadSet new_lookaheads;
        for (auto entry : *cached_lookaheads.entries) {
          if (entry == PROPAGATE) {
            new_lookaheads.insert_all(next_lookaheads);
          } else {
            new_lookaheads.insert(entry);
          }
        }

        item_set_buffer.push_back({cached_item, new_lookaheads});
      }
    }
  }

  for (const auto &pair : item_set_buffer) {
    item_set->entries[pair.first].insert_all(pair.second);
  }
}

LookaheadSet ParseItemSetBuilder::get_first_set(const rules::Symbol &symbol) const {
  return first_sets.find(symbol)->second;
}

}  // namespace build_tables
}  // namespace tree_sitter
