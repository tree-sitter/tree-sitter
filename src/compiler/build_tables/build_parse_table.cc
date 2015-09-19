#include "compiler/build_tables/build_parse_table.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/get_completion_status.h"
#include "compiler/build_tables/get_metadata.h"
#include "compiler/prepared_grammar.h"
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
  unordered_map<const ParseItemSet, ParseStateId> parse_state_ids;
  vector<vector<Symbol>> productions;
  vector<pair<ParseItemSet, ParseStateId>> item_sets_to_process;
  ParseTable parse_table;
  std::set<string> conflicts;

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar),
        lexical_grammar(lex_grammar),
        conflict_manager(grammar) {}

  pair<ParseTable, const GrammarError *> build() {
    auto start_symbol = grammar.rules.empty() ? make_shared<Symbol>(0, true)
                                              : make_shared<Symbol>(0);
    ParseItem start_item(rules::START(), start_symbol, {});
    add_parse_state(
      item_set_closure(start_item, { rules::END_OF_INPUT() }, grammar));

    while (!item_sets_to_process.empty()) {
      auto pair = item_sets_to_process.back();
      ParseItemSet &item_set = pair.first;
      ParseStateId &state_id = pair.second;
      item_sets_to_process.pop_back();

      add_reduce_actions(item_set, state_id);
      add_shift_actions(item_set, state_id);
      add_shift_extra_actions(item_set, state_id);

      if (!conflicts.empty())
        return { parse_table, new GrammarError(GrammarErrorTypeParseConflict,
                                               "Unresolved conflict.\n\n" +
                                                 *conflicts.begin()) };
    }

    for (ParseStateId state = 0; state < parse_table.states.size(); state++)
      add_reduce_extra_actions(state);

    parse_table.symbols.insert(rules::ERROR());

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
    for (const auto &transition : sym_transitions(item_set, grammar)) {
      const Symbol &symbol = transition.first;
      const ParseItemSet &next_item_set = transition.second;

      ParseAction *new_action = add_action(
        state_id, symbol,
        ParseAction::Shift(0, precedence_values_for_item_set(next_item_set)),
        item_set);
      if (new_action)
        new_action->state_index = add_parse_state(next_item_set);
    }
  }

  void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &pair : item_set) {
      const ParseItem &item = pair.first;
      const set<Symbol> &lookahead_symbols = pair.second;

      CompletionStatus completion_status = get_completion_status(item.rule);
      if (completion_status.is_done) {
        ParseAction action =
          (item.lhs == rules::START())
            ? ParseAction::Accept()
            : ParseAction::Reduce(item.lhs, item.consumed_symbols.size(),
                                  completion_status.precedence,
                                  completion_status.associativity,
                                  get_production_id(item.consumed_symbols));

        for (const auto &lookahead_sym : lookahead_symbols)
          add_action(state_id, lookahead_sym, action, item_set);
      }
    }
  }

  void add_shift_extra_actions(const ParseItemSet &item_set,
                               ParseStateId state_id) {
    for (const Symbol &ubiquitous_symbol : grammar.ubiquitous_tokens)
      add_action(state_id, ubiquitous_symbol, ParseAction::ShiftExtra(),
                 item_set);
  }

  void add_reduce_extra_actions(ParseStateId state_id) {
    const ParseItemSet item_set;
    const map<Symbol, vector<ParseAction>> &actions =
      parse_table.states[state_id].actions;

    for (const Symbol &ubiquitous_symbol : grammar.ubiquitous_tokens) {
      const auto &entry = actions.find(ubiquitous_symbol);
      if (entry == actions.end())
        continue;

      for (const auto &action : entry->second) {
        if (action.type == ParseActionTypeShift) {
          size_t shift_state_id = action.state_index;
          for (const auto &pair : actions) {
            const Symbol &lookahead_sym = pair.first;
            ParseAction reduce_extra =
              ParseAction::ReduceExtra(ubiquitous_symbol);
            add_action(shift_state_id, lookahead_sym, reduce_extra, item_set);
          }
        }
      }
    }
  }

  ParseAction *add_action(ParseStateId state_id, Symbol lookahead_sym,
                          const ParseAction &action,
                          const ParseItemSet &item_set) {
    auto &current_actions = parse_table.states[state_id].actions;
    auto current_entry = current_actions.find(lookahead_sym);
    if (current_entry == current_actions.end())
      return &parse_table.set_action(state_id, lookahead_sym, action);

    const ParseAction current_action = current_entry->second[0];
    auto resolution =
      conflict_manager.resolve(action, current_action, lookahead_sym);

    switch (resolution.second) {
      case ConflictTypeNone:
        if (resolution.first)
          return &parse_table.set_action(state_id, lookahead_sym, action);
        break;

      case ConflictTypeResolved:
        if (action.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(action.production_id);
        if (current_action.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(current_action.production_id);
        if (resolution.first)
          return &parse_table.set_action(state_id, lookahead_sym, action);
        break;

      case ConflictTypeUnresolved: {
        set<Symbol> goal_symbols = item_set_goal_symbols(item_set);
        if (has_expected_conflict(goal_symbols))
          return &parse_table.add_action(state_id, lookahead_sym, action);
        else
          conflicts.insert(conflict_description(action, current_action,
                                                lookahead_sym, goal_symbols));
        break;
      }
    }

    return nullptr;
  }

  bool has_expected_conflict(const set<Symbol> &symbols) {
    for (const auto &conflicting_symbols : grammar.expected_conflicts)
      if (symbols == conflicting_symbols)
        return true;
    return false;
  }

  set<int> precedence_values_for_item_set(const ParseItemSet &item_set) {
    set<int> result;
    for (const auto &pair : item_set) {
      const ParseItem &item = pair.first;
      if (!item.consumed_symbols.empty()) {
        auto precedence_range = get_metadata(item.rule, rules::PRECEDENCE);
        result.insert(precedence_range.min);
        result.insert(precedence_range.max);
      }
    }
    return result;
  }

  set<Symbol> item_set_goal_symbols(const ParseItemSet &item_set) {
    set<Symbol> result;
    for (const auto &pair : item_set) {
      const ParseItem &item = pair.first;
      if (!item.consumed_symbols.empty())
        result.insert(item.lhs);
    }
    return result;
  }

  string conflict_description(const ParseAction &new_action,
                              const ParseAction &old_action,
                              const rules::Symbol &symbol,
                              const set<Symbol> &goal_symbols) const {
    string symbols_string;
    bool started = false;
    for (const auto &symbol : goal_symbols) {
      if (started)
        symbols_string += ", ";
      symbols_string += symbol_name(symbol);
      started = true;
    }

    return "Within: " + symbols_string +
           "\n"
           "Lookahead: " +
           symbol_name(symbol) + "\n" +
           "Possible Actions:\n"
           "* " +
           action_description(old_action) + "\n" + "* " +
           action_description(new_action);
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
      return lexical_grammar.rules[symbol.index].name;
    } else {
      return grammar.rules[symbol.index].name;
    }
  }

  string action_description(const ParseAction &action) const {
    string result;

    switch (action.type) {
      case ParseActionTypeReduce: {
        result = "Reduce";
        for (const rules::Symbol &symbol : productions[action.production_id])
          result += " " + symbol_name(symbol);
        result += " -> " + symbol_name(action.symbol);
        break;
      }

      case ParseActionTypeShift: {
        result = "Shift";
        break;
      }

      default:
        return "";
    }

    if (action.precedence_values.size() > 1) {
      result += " (Precedences " + to_string(*action.precedence_values.begin()) +
                ", " + to_string(*action.precedence_values.rbegin()) + ")";
    } else {
      result +=
        " (Precedence " + to_string(*action.precedence_values.begin()) + ")";
    }

    return result;
  }

  size_t get_production_id(const vector<rules::Symbol> &symbols) {
    auto begin = productions.begin();
    auto end = productions.end();
    auto iter = find(begin, end, symbols);
    if (iter == end) {
      productions.push_back(symbols);
      return productions.size() - 1;
    }
    return iter - begin;
  }
};

pair<ParseTable, const GrammarError *> build_parse_table(
  const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
