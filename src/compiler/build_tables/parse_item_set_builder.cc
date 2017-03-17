#include "compiler/build_tables/parse_item_set_builder.h"
#include <set>
#include <vector>
#include <utility>
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using std::set;
using std::map;
using std::get;
using std::pair;
using std::tuple;
using std::make_tuple;
using rules::Symbol;
using rules::NONE;

ParseItemSetBuilder::ParseItemSetBuilder(const SyntaxGrammar &grammar,
                                         const LexicalGrammar &lexical_grammar) {
  vector<Symbol> symbols_to_process;
  set<Symbol::Index> processed_non_terminals;

  for (size_t i = 0, n = lexical_grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::terminal(i);
    first_sets.insert({symbol, LookaheadSet({ symbol })});
  }

  for (size_t i = 0, n = grammar.external_tokens.size(); i < n; i++) {
    Symbol symbol = Symbol::external(i);
    first_sets.insert({symbol, LookaheadSet({ symbol })});
  }

  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::non_terminal(i);
    LookaheadSet first_set;

    processed_non_terminals.clear();
    symbols_to_process.clear();
    symbols_to_process.push_back(symbol);
    while (!symbols_to_process.empty()) {
      Symbol current_symbol = symbols_to_process.back();
      symbols_to_process.pop_back();

      if (!current_symbol.is_non_terminal()) {
        first_set.insert(current_symbol);
      } else if (processed_non_terminals.insert(current_symbol.index).second) {
        for (const Production &production : grammar.variables[current_symbol.index].productions) {
          if (!production.empty()) {
            symbols_to_process.push_back(production[0].symbol);
          }
        }
      }
    }

    first_sets.insert({symbol, first_set});
  }

  vector<ParseItemSetComponent> components_to_process;

  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::non_terminal(i);
    map<ParseItem, pair<LookaheadSet, bool>> cache_entry;

    components_to_process.clear();
    for (const Production &production : grammar.variables[i].productions) {
      components_to_process.push_back(ParseItemSetComponent{
        ParseItem(symbol, production, 0),
        LookaheadSet(),
        true
      });
    }

    while (!components_to_process.empty()) {
      ParseItemSetComponent component = components_to_process.back();
      ParseItem &item = component.item;
      LookaheadSet &lookaheads = component.lookaheads;
      components_to_process.pop_back();

      bool component_is_new;
      if (component.propagates_lookaheads) {
        component_is_new = !cache_entry[item].second;
        cache_entry[item].second = true;
      } else {
        component_is_new = cache_entry[item].first.insert_all(lookaheads);
      }

      if (component_is_new) {
        Symbol next_symbol = item.next_symbol();
        if (!next_symbol.is_non_terminal() || next_symbol.is_built_in())
          continue;

        LookaheadSet next_lookaheads;
        bool propagates_lookaheads;
        size_t next_step = item.step_index + 1;
        if (next_step == item.production->size()) {
          next_lookaheads = lookaheads;
          propagates_lookaheads = component.propagates_lookaheads;
        } else {
          Symbol symbol_after_next = item.production->at(next_step).symbol;
          next_lookaheads = first_sets.find(symbol_after_next)->second;
          propagates_lookaheads = false;
        }

        for (const Production &production : grammar.variables[next_symbol.index].productions) {
          components_to_process.push_back(ParseItemSetComponent{
            ParseItem(next_symbol, production, 0),
            next_lookaheads,
            propagates_lookaheads
          });
        }
      }
    }

    for (auto &pair : cache_entry) {
      component_cache[symbol.index].push_back(ParseItemSetComponent{
        pair.first,
        pair.second.first,
        pair.second.second
      });
    }
  }
}

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  item_set_buffer.clear();

  for (const auto &pair : item_set->entries) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookaheads = pair.second;

    const Symbol &next_symbol = item.next_symbol();
    if (next_symbol.is_non_terminal() && !next_symbol.is_built_in()) {
      LookaheadSet next_lookaheads;
      size_t next_step = item.step_index + 1;
      if (next_step == item.production->size()) {
        next_lookaheads = lookaheads;
      } else {
        Symbol symbol_after_next = item.production->at(next_step).symbol;
        next_lookaheads = first_sets.find(symbol_after_next)->second;
      }

      for (const ParseItemSetComponent &component : component_cache[next_symbol.index]) {
        item_set_buffer.push_back({component.item, component.lookaheads});
        if (component.propagates_lookaheads) {
          item_set_buffer.push_back({component.item, next_lookaheads});
        }
      }
    }
  }

  for (const auto &buffer_entry : item_set_buffer) {
    item_set->entries[buffer_entry.first].insert_all(buffer_entry.second);
  }
}

LookaheadSet ParseItemSetBuilder::get_first_set(const rules::Symbol &symbol) const {
  return first_sets.find(symbol)->second;
}

}  // namespace build_tables
}  // namespace tree_sitter
