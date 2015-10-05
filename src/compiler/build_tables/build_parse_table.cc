#include "compiler/build_tables/build_parse_table.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/get_completion_status.h"
#include "compiler/build_tables/get_metadata.h"
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

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar),
        lexical_grammar(lex_grammar),
        conflict_manager(grammar) {}

  pair<ParseTable, const GrammarError *> build() {
    add_parse_state(ParseItemSet({
      {
        ParseItem(rules::START(), 0, 0, -2),
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
    for (const auto &transition : item_set.transitions(grammar)) {
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

  struct CompletionStatus {
    bool is_done;
    int precedence;
    Associativity associativity;
  };

  CompletionStatus get_completion_status(const ParseItem &item) {
    const Production &production =
      grammar.productions(item.lhs())[item.production_index];
    if (item.step_index == production.size()) {
      const ProductionStep &last_step = production[item.step_index - 1];
      return { true, last_step.precedence, last_step.associativity };
    }
    return { false, 0, AssociativityNone };
  }

  void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const auto &lookahead_symbols = pair.second;

      CompletionStatus completion_status = get_completion_status(item);
      if (completion_status.is_done) {
        ParseAction action =
          (item.lhs() == rules::START())
            ? ParseAction::Accept()
            : ParseAction::Reduce(Symbol(item.variable_index), item.step_index,
                                  completion_status.precedence,
                                  completion_status.associativity,
                                  item.production_index);

        for (const auto &lookahead_sym : *lookahead_symbols.entries)
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

  ParseAction *add_action(ParseStateId state_id, Symbol lookahead,
                          const ParseAction &new_action,
                          const ParseItemSet &item_set) {
    const auto &current_actions = parse_table.states[state_id].actions;
    const auto &current_entry = current_actions.find(lookahead);
    if (current_entry == current_actions.end())
      return &parse_table.set_action(state_id, lookahead, new_action);

    const ParseAction old_action = current_entry->second[0];
    auto resolution =
      conflict_manager.resolve(new_action, old_action, lookahead);

    switch (resolution.second) {
      case ConflictTypeNone:
        if (resolution.first)
          return &parse_table.set_action(state_id, lookahead, new_action);
        break;

      case ConflictTypeResolved: {
        if (resolution.first)
          return &parse_table.set_action(state_id, lookahead, new_action);
        if (old_action.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(production_id(old_action));
        if (new_action.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(production_id(new_action));
        break;
      }

      case ConflictTypeUnresolved: {
        auto old_goal_syms = goal_symbols(item_set, old_action, lookahead);
        auto new_goal_syms = goal_symbols(item_set, new_action, lookahead);
        if (has_expected_conflict(old_goal_syms, new_goal_syms))
          return &parse_table.add_action(state_id, lookahead, new_action);
        else
          conflicts.insert(conflict_description(
            lookahead, old_action, old_goal_syms, new_action, new_goal_syms));
        break;
      }
    }

    return nullptr;
  }

  pair<Symbol, int> production_id(const ParseAction &action) {
    return { action.symbol, action.production_id };
  }

  bool has_expected_conflict(set<Symbol> symbols1, const set<Symbol> &symbols2) {
    symbols1.insert(symbols2.begin(), symbols2.end());
    for (const auto &conflicting_symbols : grammar.expected_conflicts)
      if (symbols1 == conflicting_symbols)
        return true;
    return false;
  }

  PrecedenceRange precedence_values_for_item_set(const ParseItemSet &item_set) {
    PrecedenceRange result;
    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const Production &production =
        grammar.productions(item.lhs())[item.production_index];
      if (item.step_index > 0)
        result.add(production[item.step_index - 1].precedence);
    }
    return result;
  }

  set<Symbol> goal_symbols(const ParseItemSet &item_set,
                           const ParseAction &action,
                           const Symbol &lookahead_sym) {
    set<Symbol> result;
    switch (action.type) {
      case ParseActionTypeShift: {
        for (const auto &pair : item_set.entries) {
          const ParseItem &item = pair.first;
          const Production &production =
            grammar.productions(item.lhs())[item.production_index];
          if (item.step_index < production.size() &&
              production[item.step_index].symbol == lookahead_sym)
            result.insert(item.lhs());
        }
        break;
      }

      case ParseActionTypeReduce:
        result.insert(action.symbol);
        break;

      default:
        break;
    }
    return result;
  }

  string conflict_description(const Symbol &lookahead,
                              const ParseAction &old_action,
                              const set<Symbol> &old_goal_symbols,
                              const ParseAction &new_action,
                              const set<Symbol> &new_goal_symbols) const {
    return "Lookahead: " + symbol_name(lookahead) + "\n" +
           "Possible Actions:\n"
           "* " +
           action_description(old_action, old_goal_symbols) + "\n" + "* " +
           action_description(new_action, new_goal_symbols);
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
      return lexical_grammar.variables[symbol.index].name;
    } else {
      return grammar.variables[symbol.index].name;
    }
  }

  string action_description(const ParseAction &action,
                            const set<Symbol> &goal_symbols) const {
    string result;
    switch (action.type) {
      case ParseActionTypeReduce: {
        result += "Reduce";
        for (const ProductionStep &step :
             grammar.productions(action.symbol)[action.production_id])
          result += " " + symbol_name(step.symbol);
        result += " -> " + symbol_name(action.symbol);
        break;
      }

      case ParseActionTypeShift: {
        result += "Shift ";
        bool started = false;
        for (const auto &symbol : goal_symbols) {
          if (started)
            result += ", ";
          started = true;
          result += symbol_name(symbol);
        }
        break;
      }

      default:
        break;
    }

    result += (action.precedence_range.min == action.precedence_range.max)
                ? " (Precedence " + to_string(action.precedence_range.min) + ")"
                : " (Precedences " + to_string(action.precedence_range.min) +
                    ", " + to_string(action.precedence_range.max) + ")";

    return result;
  }
};

pair<ParseTable, const GrammarError *> build_parse_table(
  const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
