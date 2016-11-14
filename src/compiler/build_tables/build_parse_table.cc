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
#include "compiler/build_tables/parse_item_set_builder.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/build_tables/recovery_tokens.h"

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
using rules::END_OF_INPUT;

class ParseTableBuilder {
  const SyntaxGrammar grammar;
  const LexicalGrammar lexical_grammar;
  ParseConflictManager conflict_manager;
  unordered_map<Symbol, ParseItemSet> recovery_states;
  unordered_map<ParseItemSet, ParseStateId, ParseItemSet::Hash> parse_state_ids;
  vector<pair<ParseItemSet, ParseStateId>> item_sets_to_process;
  ParseTable parse_table;
  set<string> conflicts;
  ParseItemSetBuilder item_set_builder;
  set<const Production *> fragile_productions;
  bool allow_any_conflict;

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar),
        lexical_grammar(lex_grammar),
        item_set_builder(grammar, lex_grammar),
        allow_any_conflict(false) {}

  pair<ParseTable, CompileError> build() {
    Symbol start_symbol = Symbol(0, grammar.variables.empty());
    Production start_production({
      ProductionStep(start_symbol, 0, rules::AssociativityNone),
    });

    // Placeholder for error state
    add_parse_state(ParseItemSet());

    add_parse_state(ParseItemSet({
      {
        ParseItem(rules::START(), start_production, 0),
        LookaheadSet({ END_OF_INPUT().index }),
      },
    }));

    CompileError error = process_part_state_queue();
    if (error.type != TSCompileErrorTypeNone)
      return { parse_table, error };

    parse_table.mergeable_symbols = recovery_tokens(lexical_grammar);

    build_error_parse_state();

    allow_any_conflict = true;
    process_part_state_queue();
    allow_any_conflict = false;

    mark_fragile_actions();
    remove_duplicate_parse_states();

    return { parse_table, CompileError::none() };
  }

 private:
  CompileError process_part_state_queue() {
    while (!item_sets_to_process.empty()) {
      auto pair = item_sets_to_process.back();
      ParseItemSet &item_set = pair.first;
      ParseStateId state_id = pair.second;
      item_sets_to_process.pop_back();

      item_set_builder.apply_transitive_closure(&item_set);
      add_reduce_actions(item_set, state_id);
      add_shift_actions(item_set, state_id);
      add_shift_extra_actions(state_id);

      if (!conflicts.empty()) {
        return CompileError(TSCompileErrorTypeParseConflict,
                            "Unresolved conflict.\n\n" + *conflicts.begin());
      }
    }

    return CompileError::none();
  }

  void build_error_parse_state() {
    ParseState error_state;

    for (const Symbol::Index index : parse_table.mergeable_symbols) {
      add_out_of_context_parse_state(&error_state, Symbol(index, true));
    }

    for (const Symbol &symbol : grammar.extra_tokens) {
      if (!error_state.terminal_entries.count(symbol.index)) {
        error_state.terminal_entries[symbol.index].actions.push_back(ParseAction::ShiftExtra());
      }
    }

    for (size_t i = 0; i < grammar.variables.size(); i++) {
      add_out_of_context_parse_state(&error_state, Symbol(i, false));
    }

    error_state.terminal_entries[END_OF_INPUT().index].actions.push_back(ParseAction::Recover(0));
    parse_table.states[0] = error_state;
  }

  void add_out_of_context_parse_state(ParseState *error_state,
                                      const rules::Symbol &symbol) {
    const ParseItemSet &item_set = recovery_states[symbol];
    if (!item_set.entries.empty()) {
      ParseStateId state = add_parse_state(item_set);
      if (symbol.is_token) {
        error_state->terminal_entries[symbol.index].actions.assign({ ParseAction::Recover(state) });
      } else {
        error_state->nonterminal_entries[symbol.index] = state;
      }
    }
  }

  ParseStateId add_parse_state(const ParseItemSet &item_set) {
    auto pair = parse_state_ids.find(item_set);
    if (pair == parse_state_ids.end()) {
      ParseStateId state_id = parse_table.add_state();

      parse_state_ids[item_set] = state_id;
      item_sets_to_process.push_back({ std::move(item_set), state_id });
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

      if (!allow_any_conflict) {
        recovery_states[symbol].add(next_item_set);
      }

      if (symbol.is_token) {
        ParseAction *new_action = add_terminal_action(
          state_id, symbol.index, ParseAction::Shift(0, precedence), item_set);
        if (new_action) {
          new_action->state_index = add_parse_state(next_item_set);
        }
      } else {
        parse_table.set_nonterminal_action(state_id, symbol.index, add_parse_state(next_item_set));
      }
    }
  }

  void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const auto &lookahead_symbols = pair.second;

      ParseItem::CompletionStatus status = item.completion_status();
      if (status.is_done) {
        ParseAction action;
        if (item.lhs() == rules::START()) {
          action = ParseAction::Accept();
        } else {
          action = ParseAction::Reduce(Symbol(item.variable_index),
                                       item.step_index, status.precedence,
                                       status.associativity, *item.production);
        }

        for (const Symbol::Index lookahead : *lookahead_symbols.entries) {
          add_terminal_action(state_id, lookahead, action, item_set);
        }
      }
    }
  }

  void add_shift_extra_actions(ParseStateId state_id) {
    ParseAction action = ParseAction::ShiftExtra();
    ParseState &state = parse_table.states[state_id];
    for (const Symbol &extra_symbol : grammar.extra_tokens)
      if (!state.terminal_entries.count(extra_symbol.index) ||
          state.has_shift_action() || allow_any_conflict)
        parse_table.add_terminal_action(state_id, extra_symbol.index, action);
  }

  void mark_fragile_actions() {
    for (ParseState &state : parse_table.states) {
      set<Symbol> symbols_with_multiple_actions;

      for (auto &entry : state.terminal_entries) {
        const Symbol symbol(entry.first, true);
        auto &actions = entry.second.actions;

        if (actions.size() > 1) {
          symbols_with_multiple_actions.insert(symbol);
        }

        for (ParseAction &action : actions) {
          if (action.type == ParseActionTypeReduce) {
            if (has_fragile_production(action.production))
              action.fragile = true;

            action.production = NULL;
            action.precedence_range = PrecedenceRange();
            action.associativity = rules::AssociativityNone;
          }
        }

        for (auto i = actions.begin(); i != actions.end();) {
          bool erased = false;
          for (auto j = actions.begin(); j != i; j++) {
            if (*j == *i) {
              actions.erase(i);
              erased = true;
              break;
            }
          }
          if (!erased) {
            ++i;
          }
        }
      }
    }
  }

  void remove_duplicate_parse_states() {
    remove_duplicate_states<ParseTable>(&parse_table);
  }

  ParseAction *add_terminal_action(ParseStateId state_id, Symbol::Index lookahead,
                                   const ParseAction &new_action,
                                   const ParseItemSet &item_set) {
    const ParseState &state = parse_table.states[state_id];
    const auto &current_entry = state.terminal_entries.find(lookahead);
    if (current_entry == state.terminal_entries.end())
      return &parse_table.set_terminal_action(state_id, lookahead, new_action);
    if (allow_any_conflict)
      return &parse_table.add_terminal_action(state_id, lookahead, new_action);

    const ParseAction old_action = current_entry->second.actions[0];
    auto resolution = conflict_manager.resolve(new_action, old_action);

    switch (resolution.second) {
      case ConflictTypeNone:
        if (resolution.first) {
          return &parse_table.set_terminal_action(state_id, lookahead, new_action);
        }
        break;

      case ConflictTypeResolved: {
        if (resolution.first) {
          if (old_action.type == ParseActionTypeReduce)
            fragile_productions.insert(old_action.production);
          return &parse_table.set_terminal_action(state_id, lookahead, new_action);
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
          return &parse_table.add_terminal_action(state_id, lookahead, new_action);
        }
        break;
      }
    }

    return nullptr;
  }

  bool handle_unresolved_conflict(const ParseItemSet &item_set,
                                  const Symbol::Index lookahead) {
    set<Symbol> involved_symbols;
    set<ParseItem> reduce_items;
    set<ParseItem> core_shift_items;
    set<ParseItem> other_shift_items;

    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const LookaheadSet &lookahead_set = pair.second;

      Symbol next_symbol = item.next_symbol();
      if (next_symbol == rules::NONE()) {
        if (lookahead_set.contains(lookahead)) {
          involved_symbols.insert(item.lhs());
          reduce_items.insert(item);
        }
      } else {
        if (item.step_index > 0) {
          LookaheadSet first_set = item_set_builder.get_first_set(next_symbol);
          if (first_set.contains(lookahead)) {
            involved_symbols.insert(item.lhs());
            core_shift_items.insert(item);
          }
        } else if (next_symbol.is_token && next_symbol.index == lookahead) {
          other_shift_items.insert(item);
        }
      }
    }

    for (const auto &conflict_set : grammar.expected_conflicts)
      if (involved_symbols == conflict_set)
        return true;

    string description = "Lookahead symbol: " + symbol_name(Symbol(lookahead, true)) + "\n";

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
      if (symbol == END_OF_INPUT())
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

pair<ParseTable, CompileError> build_parse_table(
  const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
