#include "compiler/build_tables/build_parse_table.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/build_tables/remove_duplicate_states.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

using std::find;
using std::pair;
using std::vector;
using std::set;
using std::map;
using std::string;
using std::to_string;
using std::unordered_map;
using std::make_shared;
using rules::Symbol;

class ParseTableBuilder {
  const SyntaxGrammar grammar;
  const LexicalGrammar lexical_grammar;
  ParseConflictManager conflict_manager;
  unordered_map<ParseItemSet, ParseStateId, ParseItemSet::Hash> parse_state_ids;
  vector<pair<ParseItemSet, ParseStateId>> item_sets_to_process;
  ParseTable parse_table;
  std::set<string> conflicts;
  ParseItemSet null_item_set;
  std::set<const Production *> fragile_productions;

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar), lexical_grammar(lex_grammar) {}

  pair<ParseTable, const GrammarError *> build() {
    Symbol start_symbol = Symbol(0, grammar.variables.empty());
    Production start_production({
      ProductionStep(start_symbol, 0, rules::AssociativityNone),
    });

    add_parse_state(ParseItemSet({
      {
        ParseItem(rules::START(), start_production, 0),
        LookaheadSet({ rules::END_OF_INPUT() }),
      },
    }));

    while (!item_sets_to_process.empty()) {
      auto pair = item_sets_to_process.back();
      ParseItemSet item_set = item_set_closure(pair.first, grammar);
      ParseStateId state_id = pair.second;
      item_sets_to_process.pop_back();

      add_reduce_actions(item_set, state_id);
      add_shift_actions(item_set, state_id);

      if (!conflicts.empty())
        return { parse_table, new GrammarError(GrammarErrorTypeParseConflict,
                                               "Unresolved conflict.\n\n" +
                                                 *conflicts.begin()) };
    }

    for (ParseStateId state = 0; state < parse_table.states.size(); state++) {
      add_shift_extra_actions(state);
      add_reduce_extra_actions(state);
    }

    mark_fragile_actions();
    remove_duplicate_parse_states();

    parse_table.symbols.insert({ rules::ERROR(), {} });

    return { parse_table, nullptr };
  }

 private:
  ParseStateId add_parse_state(const ParseItemSet &item_set) {
    auto pair = parse_state_ids.find(item_set);
    if (pair == parse_state_ids.end()) {
      ParseStateId state_id = parse_table.add_state();
      parse_state_ids[item_set] = state_id;
      item_sets_to_process.push_back({ item_set, state_id });
      return state_id;
    } else {
      return pair->second;
    }
  }

  void add_shift_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &transition : item_set.transitions()) {
      const Symbol &symbol = transition.first;
      const ParseItemSet &next_item_set = transition.second.first;
      const PrecedenceRange &precedence = transition.second.second;

      ParseAction *new_action = add_action(
        state_id, symbol, ParseAction::Shift(0, precedence), item_set);
      if (new_action)
        new_action->state_index = add_parse_state(next_item_set);
    }
  }

  void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const auto &lookahead_symbols = pair.second;

      ParseItem::CompletionStatus status = item.completion_status();
      if (status.is_done) {
        ParseAction action =
          (item.lhs() == rules::START())
            ? ParseAction::Accept()
            : ParseAction::Reduce(Symbol(item.variable_index), item.step_index,
                                  status.precedence, status.associativity,
                                  *item.production);

        for (const auto &lookahead_sym : *lookahead_symbols.entries)
          add_action(state_id, lookahead_sym, action, item_set);
      }
    }
  }

  void add_shift_extra_actions(ParseStateId state_id) {
    ParseAction action = ParseAction::ShiftExtra();
    for (const Symbol &extra_symbol : grammar.extra_tokens)
      add_action(state_id, extra_symbol, action, null_item_set);
  }

  void add_reduce_extra_actions(ParseStateId state_id) {
    const ParseState &state = parse_table.states[state_id];

    for (const Symbol &extra_symbol : grammar.extra_tokens) {
      const auto &actions_for_symbol = state.actions.find(extra_symbol);
      if (actions_for_symbol == state.actions.end())
        continue;

      for (const ParseAction &action : actions_for_symbol->second)
        if (action.type == ParseActionTypeShift && !action.extra) {
          size_t dest_state_id = action.state_index;
          ParseAction reduce_extra = ParseAction::ReduceExtra(extra_symbol);
          for (const auto &pair : state.actions)
            add_action(dest_state_id, pair.first, reduce_extra, null_item_set);
        }
    }
  }

  void mark_fragile_actions() {
    for (ParseState &state : parse_table.states) {
      set<Symbol> symbols_with_multiple_actions;

      for (auto &entry : state.actions) {
        if (entry.second.size() > 1)
          symbols_with_multiple_actions.insert(entry.first);

        for (ParseAction &action : entry.second) {
          if (action.type == ParseActionTypeReduce && !action.extra) {
            if (has_fragile_production(action.production))
              action.fragile = true;

            action.production = NULL;
            action.precedence_range = PrecedenceRange();
            action.associativity = rules::AssociativityNone;
          }
        }
      }

      if (!symbols_with_multiple_actions.empty()) {
        for (auto &entry : state.actions) {
          if (!entry.first.is_token) {
            set<Symbol> first_set = get_first_set(entry.first);
            for (const Symbol &symbol : symbols_with_multiple_actions) {
              if (first_set.count(symbol)) {
                entry.second[0].can_hide_split = true;
                break;
              }
            }
          }
        }
      }
    }
  }

  void remove_duplicate_parse_states() {
    remove_duplicate_states<ParseState, ParseAction, ParseActionTypeShift>(
      &parse_table.states);
  }

  ParseAction *add_action(ParseStateId state_id, Symbol lookahead,
                          const ParseAction &new_action,
                          const ParseItemSet &item_set) {
    const auto &current_actions = parse_table.states[state_id].actions;
    const auto &current_entry = current_actions.find(lookahead);
    if (current_entry == current_actions.end())
      return &parse_table.set_action(state_id, lookahead, new_action);

    const ParseAction old_action = current_entry->second[0];
    auto resolution = conflict_manager.resolve(new_action, old_action);

    switch (resolution.second) {
      case ConflictTypeNone:
        if (resolution.first)
          return &parse_table.set_action(state_id, lookahead, new_action);
        break;

      case ConflictTypeResolved: {
        if (resolution.first) {
          if (old_action.type == ParseActionTypeReduce)
            fragile_productions.insert(old_action.production);
          return &parse_table.set_action(state_id, lookahead, new_action);
        } else {
          if (new_action.type == ParseActionTypeReduce)
            fragile_productions.insert(new_action.production);
          break;
        }
      }

      case ConflictTypeUnresolved: {
        if (handle_unresolved_conflict(item_set, lookahead)) {
          if (old_action.type == ParseActionTypeReduce)
            fragile_productions.insert(old_action.production);
          if (new_action.type == ParseActionTypeReduce)
            fragile_productions.insert(new_action.production);
          return &parse_table.add_action(state_id, lookahead, new_action);
        }
        break;
      }
    }

    return nullptr;
  }

  bool handle_unresolved_conflict(const ParseItemSet &item_set,
                                  const Symbol &lookahead) {
    set<Symbol> involved_symbols;
    set<ParseItem> reduce_items;
    set<ParseItem> core_shift_items;
    set<ParseItem> other_shift_items;

    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const LookaheadSet &lookahead_set = pair.second;

      if (item.step_index == item.production->size()) {
        if (lookahead_set.contains(lookahead)) {
          involved_symbols.insert(item.lhs());
          reduce_items.insert(item);
        }
      } else {
        Symbol next_symbol = item.production->at(item.step_index).symbol;

        if (item.step_index > 0) {
          set<Symbol> first_set = get_first_set(next_symbol);
          if (first_set.count(lookahead)) {
            involved_symbols.insert(item.lhs());
            core_shift_items.insert(item);
          }
        } else if (next_symbol == lookahead) {
          other_shift_items.insert(item);
        }
      }
    }

    for (const auto &conflict_set : grammar.expected_conflicts)
      if (involved_symbols == conflict_set)
        return true;

    string description = "Lookahead symbol: " + symbol_name(lookahead) + "\n";

    if (!reduce_items.empty()) {
      description += "Reduce items:\n";
      for (const ParseItem &item : reduce_items)
        description += "  " + item_string(item) + "\n";
    }

    if (!core_shift_items.empty()) {
      description += "Core shift items:\n";
      for (const ParseItem &item : core_shift_items)
        description += "  " + item_string(item) + "\n";
    }

    if (!other_shift_items.empty()) {
      description += "Other shift items:\n";
      for (const ParseItem &item : other_shift_items)
        description += "  " + item_string(item) + "\n";
    }

    conflicts.insert(description);
    return false;
  }

  string item_string(const ParseItem &item) const {
    string result = symbol_name(item.lhs()) + " ->";
    size_t i = 0;
    for (const ProductionStep &step : *item.production) {
      if (i == item.step_index)
        result += " \u2022";
      result += " " + symbol_name(step.symbol);
      i++;
    }
    if (i == item.step_index)
      result += " \u2022";

    result += "   (prec " + to_string(item.precedence());

    switch (item.associativity()) {
      case rules::AssociativityNone:
        result += ")";
        break;
      case rules::AssociativityLeft:
        result += ", assoc left)";
        break;
      case rules::AssociativityRight:
        result += ", assoc right)";
        break;
    }

    return result;
  }

  set<Symbol> get_first_set(const Symbol &start_symbol) {
    set<Symbol> result;
    vector<Symbol> symbols_to_process({ start_symbol });

    while (!symbols_to_process.empty()) {
      Symbol symbol = symbols_to_process.back();
      symbols_to_process.pop_back();
      if (result.insert(symbol).second)
        for (const Production &production : grammar.productions(symbol))
          if (!production.empty())
            symbols_to_process.push_back(production[0].symbol);
    }

    return result;
  }

  string symbol_name(const rules::Symbol &symbol) const {
    if (symbol.is_built_in()) {
      if (symbol == rules::ERROR())
        return "ERROR";
      else if (symbol == rules::END_OF_INPUT())
        return "END_OF_INPUT";
      else
        return "";
    } else if (symbol.is_token) {
      const Variable &variable = lexical_grammar.variables[symbol.index];
      if (variable.type == VariableTypeNamed)
        return variable.name;
      else
        return "'" + variable.name + "'";
    } else {
      return grammar.variables[symbol.index].name;
    }
  }

  bool has_fragile_production(const Production *production) {
    auto end = fragile_productions.end();
    return std::find(fragile_productions.begin(), end, production) != end;
  }
};

pair<ParseTable, const GrammarError *> build_parse_table(
  const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
