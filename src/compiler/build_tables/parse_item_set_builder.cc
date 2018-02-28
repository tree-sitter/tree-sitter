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

struct FollowSetInfo {
  LookaheadSet lookaheads;
  bool propagates_lookaheads;
};

struct NonTerminalQueueEntry {
  Symbol::Index non_terminal;
  LookaheadSet lookaheads;
  bool propagates_lookaheads;
};

bool ParseItemSetBuilder::ParseItemSetComponent::operator==(
  const ParseItemSetBuilder::ParseItemSetComponent &other) const {
  return item == other.item &&
    lookaheads == other.lookaheads &&
    propagates_lookaheads == other.propagates_lookaheads;
}

template <typename T>
inline void find_or_push(vector<T> &vector, const T &item) {
  if (find(vector.begin(), vector.end(), item) == vector.end()) {
    vector.push_back(item);
  }
}

ParseItemSetBuilder::ParseItemSetBuilder(
  const SyntaxGrammar &grammar,
  const LexicalGrammar &lexical_grammar
) : grammar{grammar} {

  // Populate the FIRST and LAST set of each terminal, which just contains the terminal itself.
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

  // Populate the FIRST and LAST set of each non-terminal by recursively expanding non-terminals.
  vector<Symbol> symbols_to_process;
  set<Symbol::Index> processed_non_terminals;
  for (size_t i = 0, n = grammar.variables.size(); i < n; i++) {
    Symbol symbol = Symbol::non_terminal(i);
    LookaheadSet &first_set = first_sets[symbol];
    LookaheadSet &last_set = last_sets[symbol];

    processed_non_terminals.clear();
    symbols_to_process.assign({symbol});
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

    processed_non_terminals.clear();
    symbols_to_process.assign({symbol});
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
  }

  // Populate a cache of which ParseItems will be created when a given non-terminal is expanded.
  vector<NonTerminalQueueEntry> non_terminal_queue;
  for (Symbol::Index i = 0, n = grammar.variables.size(); i < n; i++) {

    // Compute the follow set of each *other* non-terminal that the current non-terminal can
    // start with.
    unordered_map<Symbol::Index, FollowSetInfo> follow_set_info_by_non_terminal;
    non_terminal_queue.assign({{i, LookaheadSet(), true}});
    while (!non_terminal_queue.empty()) {
      NonTerminalQueueEntry queue_entry = non_terminal_queue.back();
      non_terminal_queue.pop_back();

      bool queue_entry_is_new;
      auto &follow_set_info = follow_set_info_by_non_terminal[queue_entry.non_terminal];
      if (queue_entry.propagates_lookaheads) {
        queue_entry_is_new = !follow_set_info.propagates_lookaheads;
        follow_set_info.propagates_lookaheads = true;
      } else {
        queue_entry_is_new = follow_set_info.lookaheads.insert_all(queue_entry.lookaheads);
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

          non_terminal_queue.push_back({
            next_symbol.index,
            next_lookaheads,
            propagates_lookaheads
          });
        }
      }
    }

    // Use these follow sets to populate the cache of ParseItems for non-terminal `i`.
    for (auto &pair : follow_set_info_by_non_terminal) {
      Symbol non_terminal = Symbol::non_terminal(pair.first);

      for (const Production &production : grammar.variables[non_terminal.index].productions) {
        ParseItem item(non_terminal, production, 0);

        if (grammar.variables_to_inline.count(item.next_symbol())) {
          for (const Production &inlined_production : inline_production(item)) {
            find_or_push(transitive_closure_component_cache[i], {
              ParseItem(non_terminal, inlined_production, 0),
              pair.second.lookaheads,
              pair.second.propagates_lookaheads
            });
          }
        } else if (!grammar.variables_to_inline.count(non_terminal)) {
          find_or_push(transitive_closure_component_cache[i], {
            item,
            pair.second.lookaheads,
            pair.second.propagates_lookaheads
          });
        }
      }
    }
  }
}

const vector<Production> &ParseItemSetBuilder::inline_production(const ParseItem &item) {
  vector<Production> &result = inlined_productions_by_original_production[item];
  if (!result.empty()) return result;

  auto &inlined_step = item.production->at(item.step_index);
  vector<const Production *> productions_to_insert;
  for (auto &production : grammar.variables[inlined_step.symbol.index].productions) {
    productions_to_insert.push_back(&production);
  }

  for (auto iter = productions_to_insert.begin(); iter != productions_to_insert.end();) {
    const Production *production = *iter;

    if (!production->empty() && grammar.variables_to_inline.count(production->steps.front().symbol)) {
      iter = productions_to_insert.erase(iter);
      for (auto &inlined_production : inline_production(ParseItem(inlined_step.symbol, *production, 0))) {
        iter = productions_to_insert.insert(iter, &inlined_production);
      }
    } else {
      ++iter;
    }
  }

  for (const Production *production_to_insert : productions_to_insert) {
    auto begin = item.production->steps.begin();
    auto end = item.production->steps.end();
    auto step = begin + item.step_index;
    Production production({begin, step}, item.production->dynamic_precedence);

    for (auto &step : *production_to_insert) {
      production.steps.push_back(step);
      if (!inlined_step.alias.value.empty()) {
        production.steps.back().alias = inlined_step.alias;
      }
    }

    if (!production.back().precedence) {
      production.back().precedence = inlined_step.precedence;
    }
    if (!production.back().associativity) {
      production.back().associativity = inlined_step.associativity;
    }
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

void ParseItemSetBuilder::apply_transitive_closure(ParseItemSet *item_set) {
  for (auto iter = item_set->entries.begin(), end = item_set->entries.end(); iter != end;) {
    const ParseItem &item = iter->first;
    const LookaheadSet &lookaheads = iter->second;

    // Items whose `step_index` is 0 are not part of the item set's "kernel"; they have been
    // added in previous iterations of this loop, and they don't need to be further processed.
    if (item.lhs() == rules::START() || item.step_index > 0) {

      // Kernel items whose next symbol is a non-terminal are expanded using the pre-computed
      // parse item cache.
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

        for (const auto &component : transitive_closure_component_cache[next_symbol.index]) {
          LookaheadSet &current_lookaheads = item_set->entries[component.item];
          current_lookaheads.insert_all(component.lookaheads);
          if (component.propagates_lookaheads) {
            current_lookaheads.insert_all(next_lookaheads);
          }
        }

        if (grammar.variables_to_inline.count(next_symbol)) {
          for (const Production &inlined_production : inline_production(item)) {
            item_set->entries.insert({
              ParseItem(item.lhs(), inlined_production, item.step_index),
              lookaheads
            });
          }

          iter = item_set->entries.erase(iter);
          continue;
        }
      }
    }

    if (grammar.variables_to_inline.count(item.lhs())) {
      iter = item_set->entries.erase(iter);
      continue;
    }

    ++iter;
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
