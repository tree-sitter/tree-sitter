#include "compiler/build_tables/parse_item_set_builder.h"
#include <cassert>
#include <set>
#include <unordered_map>
#include <vector>
#include <utility>
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using std::set;
using std::get;
using std::pair;
using std::tuple;
using std::unordered_map;
using std::make_tuple;
using rules::Symbol;
using rules::NONE;

ParseItemSetBuilder::ParseItemSetBuilder(const SyntaxGrammar &grammar,
                                         const LexicalGrammar &lexical_grammar) {
  vector<Symbol> symbols_to_process;
  set<Symbol::Index> processed_non_terminals;

  for (size_t i = 0, n = lexical_grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::terminal(i);
    first_sets.insert({symbol, LookaheadSet({symbol})});
    last_sets.insert({symbol, LookaheadSet({symbol})});
  }

  for (size_t i = 0, n = grammar.external_tokens.size(); i < n; i++) {
    Symbol symbol = Symbol::external(i);
    first_sets.insert({symbol, LookaheadSet({symbol})});
    last_sets.insert({symbol, LookaheadSet({symbol})});
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

    LookaheadSet last_set;
    processed_non_terminals.clear();
    symbols_to_process.clear();
    symbols_to_process.push_back(symbol);
    while (!symbols_to_process.empty()) {
      Symbol current_symbol = symbols_to_process.back();
      symbols_to_process.pop_back();

      if (!current_symbol.is_non_terminal()) {
        last_set.insert(current_symbol);
      } else if (processed_non_terminals.insert(current_symbol.index).second) {
        for (const Production &production : grammar.variables[current_symbol.index].productions) {
          if (!production.empty()) {
            symbols_to_process.push_back(production.back().symbol);
          }
        }
      }
    }

    last_sets.insert({symbol, last_set});
  }

  struct NonTerminalQueueEntry {
    Symbol::Index non_terminal;
    LookaheadSet lookaheads;
    bool propagates_lookaheads;
  };

  vector<NonTerminalQueueEntry> non_terminal_queue_entry;

  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::non_terminal(i);

    unordered_map<Symbol::Index, pair<LookaheadSet, bool>> cached_lookaheads_by_non_terminal;

    non_terminal_queue_entry.clear();
    non_terminal_queue_entry.push_back({
      symbol.index,
      LookaheadSet(),
      true
    });

    while (!non_terminal_queue_entry.empty()) {
      NonTerminalQueueEntry queue_entry = non_terminal_queue_entry.back();
      non_terminal_queue_entry.pop_back();

      bool queue_entry_is_new;
      auto &cache_entry = cached_lookaheads_by_non_terminal[queue_entry.non_terminal];
      if (queue_entry.propagates_lookaheads) {
        queue_entry_is_new = !cache_entry.second;
        cache_entry.second = true;
      } else {
        queue_entry_is_new = cache_entry.first.insert_all(queue_entry.lookaheads);
      }

      if (queue_entry_is_new) {
        for (const Production &production : grammar.variables[queue_entry.non_terminal].productions) {
          if (production.empty()) continue;
          Symbol next_symbol = production.at(0).symbol;
          if (!next_symbol.is_non_terminal() || next_symbol.is_built_in()) continue;

          LookaheadSet next_lookaheads;
          bool propagates_lookaheads;
          if (production.size() == 1) {
            next_lookaheads = queue_entry.lookaheads;
            propagates_lookaheads = queue_entry.propagates_lookaheads;
          } else {
            Symbol symbol_after_next = production.at(1).symbol;
            next_lookaheads = first_sets.find(symbol_after_next)->second;
            propagates_lookaheads = false;
          }

          non_terminal_queue_entry.push_back({
            next_symbol.index,
            next_lookaheads,
            propagates_lookaheads
          });
        }
      }
    }

    for (auto &pair : cached_lookaheads_by_non_terminal) {
      for (const Production &production : grammar.variables[pair.first].productions) {
        component_cache[i].push_back({
          ParseItem(Symbol::non_terminal(pair.first), production, 0),
          pair.second.first,
          pair.second.second
        });
      }
    }
  }
}

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  for (const auto &pair : item_set->entries) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookaheads = pair.second;
    if (item.lhs() != rules::START() && item.step_index == 0) continue;

    const Symbol &next_symbol = item.next_symbol();
    if (!next_symbol.is_non_terminal() || next_symbol.is_built_in()) continue;

    LookaheadSet next_lookaheads;
    size_t next_step = item.step_index + 1;
    if (next_step == item.production->size()) {
      next_lookaheads = lookaheads;
    } else {
      Symbol symbol_after_next = item.production->at(next_step).symbol;
      next_lookaheads = first_sets.find(symbol_after_next)->second;
    }

    for (const ParseItemSetComponent &component : component_cache[next_symbol.index]) {
      LookaheadSet &current_lookaheads = item_set->entries[component.item];
      current_lookaheads.insert_all(component.lookaheads);
      if (component.propagates_lookaheads) current_lookaheads.insert_all(next_lookaheads);
    }
  }
}

LookaheadSet ParseItemSetBuilder::get_first_set(const rules::Symbol &symbol) const {
  return first_sets.find(symbol)->second;
}

LookaheadSet ParseItemSetBuilder::get_last_set(const rules::Symbol &symbol) const {
  return last_sets.find(symbol)->second;
}

}  // namespace build_tables
}  // namespace tree_sitter
