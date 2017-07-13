#include "compiler/build_tables/parse_item_set_builder.h"
#include <algorithm>
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

using std::find;
using std::get;
using std::move;
using std::pair;
using std::set;
using std::unordered_map;
using std::vector;
using rules::Symbol;

static vector<Production> inline_production(const ParseItem &item, const SyntaxGrammar &grammar) {
  vector<Production> result;
  for (const Production &production_to_insert : grammar.variables[item.next_symbol().index].productions) {
    auto begin = item.production->steps.begin();
    auto end = item.production->steps.end();
    auto step = begin + item.step_index;

    Production production{{begin, step}, item.production->dynamic_precedence};
    production.steps.insert(
      production.steps.end(),
      production_to_insert.steps.begin(),
      production_to_insert.steps.end()
    );
    production.back().precedence = item.precedence();
    production.back().associativity = item.associativity();
    production.steps.insert(
      production.steps.end(),
      step + 1,
      end
    );

    if (find(result.begin(), result.end(), production) == result.end()) {
      result.push_back(move(production));
    }
  }
  return result;
}

ParseItemSetBuilder::ParseItemSetBuilder(const SyntaxGrammar &grammar,
                                         const LexicalGrammar &lexical_grammar) : grammar{grammar} {
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
        Symbol lhs = Symbol::non_terminal(pair.first);
        ParseItem item(lhs, production, 0);

        if (grammar.variables_to_inline.count(item.next_symbol())) {
          vector<Production> &inlined_productions = inlined_productions_by_original_production[item];
          if (inlined_productions.empty()) {
            inlined_productions = inline_production(item, grammar);
          }

          for (const Production &inlined_production : inlined_productions) {
            ParseItemSetComponent component{
              ParseItem(lhs, inlined_production, 0),
              pair.second.first,
              pair.second.second
            };

            if (find(component_cache[i].begin(), component_cache[i].end(), component) == component_cache[i].end()) {
              component_cache[i].push_back(component);
            }
          }
        } else if (!grammar.variables_to_inline.count(lhs)) {
          ParseItemSetComponent component{
            ParseItem(lhs, production, 0),
            pair.second.first,
            pair.second.second
          };

          if (find(component_cache[i].begin(), component_cache[i].end(), component) == component_cache[i].end()) {
            component_cache[i].push_back(component);
          }
        }
      }
    }
  }
}

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  for (auto iter = item_set->entries.begin(), end = item_set->entries.end(); iter != end;) {
    const ParseItem &item = iter->first;
    const LookaheadSet &lookaheads = iter->second;
    if (item.lhs() != rules::START() && item.step_index == 0) {
      ++iter;
      continue;
    }

    const Symbol &next_symbol = item.next_symbol();
    if (!next_symbol.is_non_terminal() || next_symbol.is_built_in()) {
      ++iter;
      continue;
    }

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

    if (grammar.variables_to_inline.count(next_symbol)) {
      vector<Production> &inlined_productions = inlined_productions_by_original_production[item];
      if (inlined_productions.empty()) {
        inlined_productions = inline_production(item, grammar);
      }

      for (const Production &inlined_production : inlined_productions) {
        item_set->entries.insert({
          ParseItem(item.lhs(), inlined_production, item.step_index),
          lookaheads
        });
      }

      iter = item_set->entries.erase(iter);
    } else {
      ++iter;
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
