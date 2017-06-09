#include "compiler/build_tables/build_parse_table.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/parse_item_set_builder.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rule.h"
#include "compiler/build_tables/lex_table_builder.h"

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
using rules::Associativity;
using rules::Symbol;
using rules::END_OF_INPUT;

class ParseTableBuilder {
  const SyntaxGrammar grammar;
  const LexicalGrammar lexical_grammar;
  unordered_map<Symbol, ParseItemSet> recovery_states;
  unordered_map<ParseItemSet, ParseStateId> parse_state_ids;
  vector<pair<ParseItemSet, ParseStateId>> item_sets_to_process;
  ParseTable parse_table;
  set<string> conflicts;
  ParseItemSetBuilder item_set_builder;
  set<const Production *> fragile_productions;
  vector<set<Symbol>> incompatible_tokens_by_index;
  bool allow_any_conflict;

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar),
        lexical_grammar(lex_grammar),
        item_set_builder(grammar, lex_grammar),
        allow_any_conflict(false) {}

  pair<ParseTable, CompileError> build() {
    Symbol start_symbol = grammar.variables.empty() ?
      Symbol::terminal(0) :
      Symbol::non_terminal(0);

    Production start_production{
      ProductionStep{start_symbol, 0, rules::AssociativityNone},
    };

    // Placeholder for error state
    add_parse_state(ParseItemSet());

    add_parse_state(ParseItemSet({
      {
        ParseItem(rules::START(), start_production, 0),
        LookaheadSet({ END_OF_INPUT() }),
      },
    }));

    CompileError error = process_part_state_queue();
    if (error.type != TSCompileErrorTypeNone) {
      return { parse_table, error };
    }

    compute_unmergable_token_pairs();

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
      string conflict = add_actions(item_set, state_id);

      if (!conflict.empty()) {
        return CompileError(TSCompileErrorTypeParseConflict, conflict);
      }
    }

    return CompileError::none();
  }

  void build_error_parse_state() {
    ParseState error_state;

    for (unsigned i = 0; i < lexical_grammar.variables.size(); i++) {
      Symbol token = Symbol::terminal(i);
      bool has_non_reciprocal_conflict = false;

      for (Symbol incompatible_token : incompatible_tokens_by_index[i]) {
        if (incompatible_token.is_terminal() &&
            !incompatible_tokens_by_index[incompatible_token.index].count(token)) {
          has_non_reciprocal_conflict = true;
          break;
        }
      }

      if (!has_non_reciprocal_conflict) {
        add_out_of_context_parse_state(&error_state, Symbol::terminal(i));
      }
    }

    for (const Symbol &symbol : grammar.extra_tokens) {
      if (!error_state.terminal_entries.count(symbol)) {
        error_state.terminal_entries[symbol].actions.push_back(ParseAction::ShiftExtra());
      }
    }

    for (size_t i = 0; i < grammar.external_tokens.size(); i++) {
      add_out_of_context_parse_state(&error_state, Symbol::external(i));
    }

    for (size_t i = 0; i < grammar.variables.size(); i++) {
      add_out_of_context_parse_state(&error_state, Symbol::non_terminal(i));
    }

    error_state.terminal_entries[END_OF_INPUT()].actions.push_back(ParseAction::Recover(0));
    parse_table.states[0] = error_state;
  }

  void add_out_of_context_parse_state(ParseState *error_state,
                                      const rules::Symbol &symbol) {
    const ParseItemSet &item_set = recovery_states[symbol];
    if (!item_set.entries.empty()) {
      ParseStateId state = add_parse_state(item_set);
      if (symbol.is_non_terminal()) {
        error_state->nonterminal_entries[symbol.index] = state;
      } else {
        error_state->terminal_entries[symbol].actions.assign({ ParseAction::Recover(state) });
      }
    }
  }

  ParseStateId add_parse_state(const ParseItemSet &item_set) {
    auto pair = parse_state_ids.find(item_set);
    if (pair == parse_state_ids.end()) {
      ParseStateId state_id = parse_table.states.size();
      parse_table.states.push_back(ParseState());
      parse_state_ids[item_set] = state_id;
      parse_table.states[state_id].shift_actions_signature = item_set.unfinished_item_signature();
      item_sets_to_process.push_back({ std::move(item_set), state_id });
      return state_id;
    } else {
      return pair->second;
    }
  }

  string add_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    map<Symbol, ParseItemSet> terminal_successors;
    map<Symbol::Index, ParseItemSet> nonterminal_successors;
    set<Symbol> lookaheads_with_conflicts;

    for (const auto &pair : item_set.entries) {
      const ParseItem &item = pair.first;
      const LookaheadSet &lookahead_symbols = pair.second;

      // If the item is finished, immediately add a Reduce or Accept action to
      // the parse table for each of its lookahead terminals.
      if (item.is_done()) {
        ParseAction action = (item.lhs() == rules::START()) ?
          ParseAction::Accept() :
          ParseAction::Reduce(item.lhs(), item.step_index, *item.production);

        int precedence = item.precedence();
        for (Symbol lookahead : *lookahead_symbols.entries) {
          ParseTableEntry &entry = parse_table.states[state_id].terminal_entries[lookahead];

          // Only add the highest-precedence Reduce actions to the parse table.
          // If other lower-precedence actions are possible, ignore them.
          if (entry.actions.empty()) {
            parse_table.add_terminal_action(state_id, lookahead, action);
          } else {
            ParseAction &existing_action = entry.actions[0];
            if (existing_action.type == ParseActionTypeAccept || allow_any_conflict) {
              entry.actions.push_back(action);
            } else {
              int existing_precedence = existing_action.precedence();
              if (precedence > existing_precedence) {
                for (const ParseAction &old_action : entry.actions)
                  fragile_productions.insert(old_action.production);
                entry.actions.clear();
                entry.actions.push_back(action);
                lookaheads_with_conflicts.erase(lookahead);
              } else if (precedence == existing_precedence) {
                entry.actions.push_back(action);
                lookaheads_with_conflicts.insert(lookahead);
              } else {
                fragile_productions.insert(item.production);
              }
            }
          }
        }

      // If the item is unfinished, create a new item by advancing one symbol.
      // Add that new item to a successor item set.
      } else {
        Symbol symbol = item.production->at(item.step_index).symbol;
        ParseItem new_item(item.lhs(), *item.production, item.step_index + 1);

        if (symbol.is_non_terminal()) {
          nonterminal_successors[symbol.index].entries[new_item] = lookahead_symbols;
        } else {
          terminal_successors[symbol].entries[new_item] = lookahead_symbols;
        }
      }
    }

    // Add a Shift action for each possible successor state. Shift actions for
    // terminal lookaheads can conflict with Reduce actions added previously.
    for (auto &pair : terminal_successors) {
      Symbol lookahead = pair.first;
      ParseItemSet &next_item_set = pair.second;
      ParseStateId next_state_id = add_parse_state(next_item_set);
      ParseState &state = parse_table.states[state_id];
      bool had_existing_action = !state.terminal_entries[lookahead].actions.empty();
      parse_table.add_terminal_action(state_id, lookahead, ParseAction::Shift(next_state_id));
      if (!allow_any_conflict) {
        if (had_existing_action)
          lookaheads_with_conflicts.insert(lookahead);
        recovery_states[lookahead].add(next_item_set);
      }
    }

    // Add a Shift action for each non-terminal transition.
    for (auto &pair : nonterminal_successors) {
      Symbol::Index lookahead = pair.first;
      ParseItemSet &next_item_set = pair.second;
      ParseStateId next_state = add_parse_state(next_item_set);
      parse_table.set_nonterminal_action(state_id, lookahead, next_state);
      if (!allow_any_conflict)
        recovery_states[Symbol::non_terminal(lookahead)].add(next_item_set);
    }

    for (Symbol lookahead : lookaheads_with_conflicts) {
      string conflict = handle_conflict(item_set, state_id, lookahead);
      if (!conflict.empty()) return conflict;
    }

    ParseAction shift_extra = ParseAction::ShiftExtra();
    ParseState &state = parse_table.states[state_id];
    for (const Symbol &extra_symbol : grammar.extra_tokens) {
      if (!state.terminal_entries.count(extra_symbol) ||
          state.has_shift_action() || allow_any_conflict) {
        parse_table.add_terminal_action(state_id, extra_symbol, shift_extra);
      }
    }

    return "";
  }

  void mark_fragile_actions() {
    for (ParseState &state : parse_table.states) {
      for (auto &entry : state.terminal_entries) {
        auto &actions = entry.second.actions;

        for (ParseAction &action : actions) {
          if (action.type == ParseActionTypeReduce) {
            if (has_fragile_production(action.production))
              action.fragile = true;
            action.production = NULL;
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

  void compute_unmergable_token_pairs() {
    incompatible_tokens_by_index.resize(lexical_grammar.variables.size());

    auto lex_table_builder = LexTableBuilder::create(lexical_grammar);
    for (unsigned i = 0, n = lexical_grammar.variables.size(); i < n; i++) {
      Symbol token = Symbol::terminal(i);
      auto &incompatible_indices = incompatible_tokens_by_index[i];

      for (unsigned j = 0; j < n; j++) {
        if (i == j) continue;
        if (lex_table_builder->detect_conflict(i, j)) {
          incompatible_indices.insert(Symbol::terminal(j));
        }
      }

      for (const ExternalToken &external_token : grammar.external_tokens) {
        if (external_token.corresponding_internal_token == token) {
          for (unsigned j = 0; j < grammar.external_tokens.size(); j++) {
            incompatible_indices.insert(Symbol::external(j));
          }
        }
      }
    }
  }

  void remove_duplicate_parse_states() {
    map<size_t, set<ParseStateId>> state_indices_by_signature;

    for (ParseStateId i = 0, n = parse_table.states.size(); i < n; i++) {
      ParseState &state = parse_table.states[i];
      state_indices_by_signature[state.shift_actions_signature].insert(i);
    }

    set<ParseStateId> deleted_states;

    while (true) {
      map<ParseStateId, ParseStateId> state_replacements;

      for (auto &pair : state_indices_by_signature) {
        auto &state_group = pair.second;

        for (ParseStateId i : state_group) {
          for (ParseStateId j : state_group) {
            if (j == i) break;
            if (!state_replacements.count(j) && merge_parse_state(j, i)) {
              state_replacements.insert({ i, j });
              deleted_states.insert(i);
              break;
            }
          }
        }
      }

      if (state_replacements.empty()) break;

      for (ParseStateId i = 0, n = parse_table.states.size(); i < n; i++) {
        ParseState &state = parse_table.states[i];

        if (state_replacements.count(i)) {
          state_indices_by_signature[state.shift_actions_signature].erase(i);
        } else {
          state.each_referenced_state([&state_replacements](ParseStateId *state_index) {
            auto replacement = state_replacements.find(*state_index);
            if (replacement != state_replacements.end()) {
              *state_index = replacement->second;
            }
          });
        }
      }
    }

    vector<ParseStateId> new_state_ids(parse_table.states.size());
    size_t deleted_state_count = 0;
    auto deleted_state_iter = deleted_states.begin();
    for (ParseStateId i = 0; i < new_state_ids.size(); i++) {
      while (deleted_state_iter != deleted_states.end() && *deleted_state_iter < i) {
        deleted_state_count++;
        deleted_state_iter++;
      }
      new_state_ids[i] = i - deleted_state_count;
    }

    ParseStateId original_state_index = 0;
    auto iter = parse_table.states.begin();
    while (iter != parse_table.states.end()) {
      if (deleted_states.count(original_state_index)) {
        iter = parse_table.states.erase(iter);
      } else {
        ParseState &state = *iter;
        state.each_referenced_state([&new_state_ids](ParseStateId *state_index) {
          *state_index = new_state_ids[*state_index];
        });
        ++iter;
      }
      original_state_index++;
    }
  }

  static bool has_entry(const ParseState &state, const ParseTableEntry &entry) {
    for (const auto &pair : state.terminal_entries)
      if (pair.second == entry)
        return true;
    return false;
  }

  bool merge_parse_state(size_t i, size_t j) {
    ParseState &state = parse_table.states[i];
    ParseState &other = parse_table.states[j];

    if (state.nonterminal_entries != other.nonterminal_entries)
      return false;

    for (auto &entry : state.terminal_entries) {
      Symbol lookahead = entry.first;
      const vector<ParseAction> &actions = entry.second.actions;
      auto &incompatible_tokens = incompatible_tokens_by_index[lookahead.index];

      const auto &other_entry = other.terminal_entries.find(lookahead);
      if (other_entry == other.terminal_entries.end()) {
        if (lookahead.is_external()) return false;
        if (!lookahead.is_built_in()) {
          for (const Symbol &incompatible_token : incompatible_tokens) {
            if (other.terminal_entries.count(incompatible_token)) return false;
          }
        }
        if (actions.back().type != ParseActionTypeReduce)
          return false;
        if (!has_entry(other, entry.second))
          return false;
      } else if (entry.second != other_entry->second) {
        return false;
      }
    }

    set<Symbol> symbols_to_merge;

    for (auto &entry : other.terminal_entries) {
      Symbol lookahead = entry.first;
      const vector<ParseAction> &actions = entry.second.actions;
      auto &incompatible_tokens = incompatible_tokens_by_index[lookahead.index];

      if (!state.terminal_entries.count(lookahead)) {
        if (lookahead.is_external()) return false;
        if (!lookahead.is_built_in()) {
          for (const Symbol &incompatible_token : incompatible_tokens) {
            if (state.terminal_entries.count(incompatible_token)) return false;
          }
        }
        if (actions.back().type != ParseActionTypeReduce)
          return false;
        if (!has_entry(state, entry.second))
          return false;
        symbols_to_merge.insert(lookahead);
      }
    }

    for (const Symbol &lookahead : symbols_to_merge)
      state.terminal_entries[lookahead] = other.terminal_entries.find(lookahead)->second;

    return true;
  }

  string handle_conflict(const ParseItemSet &item_set, ParseStateId state_id,
                         Symbol lookahead) {
    ParseTableEntry &entry = parse_table.states[state_id].terminal_entries[lookahead];
    int reduction_precedence = entry.actions.front().precedence();
    set<ParseItem> shift_items;
    bool considered_associativity = false;

    for (const ParseAction &action : entry.actions)
      if (action.type == ParseActionTypeReduce)
        fragile_productions.insert(action.production);

    if (entry.actions.back().type == ParseActionTypeShift) {
      PrecedenceRange shift_precedence;
      for (const auto &item_set_entry : item_set.entries) {
        const ParseItem &item = item_set_entry.first;
        if (item.step_index > 0 && !item.is_done()) {
          LookaheadSet first_set = item_set_builder.get_first_set(item.next_symbol());
          if (first_set.contains(lookahead)) {
            shift_items.insert(item);
            shift_precedence.add(item.production->at(item.step_index - 1).precedence);
          }
        }
      }

      // If the shift action has higher precedence, prefer it over any of the
      // reduce actions.
      if (shift_precedence.min > reduction_precedence ||
          (shift_precedence.min == reduction_precedence &&
           shift_precedence.max > reduction_precedence)) {
        for (const ParseAction &action : entry.actions) {
          if (action.type == ParseActionTypeShift) break;
          fragile_productions.insert(action.production);
        }
        entry.actions.assign({ entry.actions.back() });
      }

      // If the shift action has lower precedence, prefer the reduce actions.
      else if (shift_precedence.max < reduction_precedence ||
          (shift_precedence.max == reduction_precedence &&
           shift_precedence.min < reduction_precedence)) {
        entry.actions.pop_back();
      }

      // If the shift action has the same precedence as the reduce actions,
      // consider the reduce actions' associativity. If they are all left
      // associative, prefer the reduce actions. If they are all right
      // associative, prefer the shift.
      else if (shift_precedence.min == reduction_precedence &&
               shift_precedence.max == reduction_precedence) {
        considered_associativity = true;
        bool has_non_associative_reductions = false;
        bool has_left_associative_reductions = false;
        bool has_right_associative_reductions = false;
        for (const ParseAction &action : entry.actions) {
          if (action.type != ParseActionTypeReduce) break;
          switch (action.associativity()) {
            case rules::AssociativityLeft:
              has_left_associative_reductions = true;
              break;
            case rules::AssociativityRight:
              has_right_associative_reductions = true;
              break;
            default:
              has_non_associative_reductions = true;
              break;
          }
        }

        if (!has_non_associative_reductions) {
          if (has_right_associative_reductions && !has_left_associative_reductions) {
            for (const ParseAction &action : entry.actions) {
              if (action.type == ParseActionTypeShift) break;
              fragile_productions.insert(action.production);
            }
            entry.actions.assign({ entry.actions.back() });
          } else if (has_left_associative_reductions && !has_right_associative_reductions) {
            entry.actions.pop_back();
          }
        }
      }
    }

    if (entry.actions.size() == 1) return "";

    set<Symbol> actual_conflict;
    for (const ParseItem &item : shift_items)
      actual_conflict.insert(item.lhs());
    for (const ParseAction &action : entry.actions)
      if (action.type == ParseActionTypeReduce)
        actual_conflict.insert(action.symbol);

    for (const auto &expected_conflict : grammar.expected_conflicts)
      if (expected_conflict == actual_conflict)
        return "";

    ParseItem earliest_starting_item;
    for (const ParseAction &action : entry.actions)
      if (action.type == ParseActionTypeReduce)
        if (action.consumed_symbol_count > earliest_starting_item.step_index)
          earliest_starting_item = ParseItem(action.symbol, *action.production, action.consumed_symbol_count);

    for (const ParseItem &shift_item : shift_items)
      if (shift_item.step_index > earliest_starting_item.step_index)
        earliest_starting_item = shift_item;

    string description = "Unresolved conflict for symbol sequence:\n\n";
    for (size_t i = 0; i < earliest_starting_item.step_index; i++) {
      description += "  " + symbol_name(earliest_starting_item.production->at(i).symbol);
    }

    description += "  \u2022  " + symbol_name(lookahead) + "  \u2026";
    description += "\n\n";

    description += "Possible interpretations:\n\n";

    size_t interpretation_count = 1;
    for (const ParseAction &action : entry.actions) {
      if (action.type == ParseActionTypeReduce) {
        description += "  " + to_string(interpretation_count++) + ":";

        for (size_t i = 0; i < earliest_starting_item.step_index - action.consumed_symbol_count; i++) {
          description += "  " + symbol_name(earliest_starting_item.production->at(i).symbol);
        }

        description += "  (" + symbol_name(action.symbol);
        for (const ProductionStep &step : *action.production) {
          description += "  " + symbol_name(step.symbol);
        }
        description += ")";
        description += "  \u2022  " + symbol_name(lookahead) + "  \u2026";
        description += "\n";
      }
    }

    for (const ParseItem &shift_item : shift_items) {
      description += "  " + to_string(interpretation_count++) + ":";

      for (size_t i = 0; i < earliest_starting_item.step_index - shift_item.step_index; i++) {
        description += "  " + symbol_name(earliest_starting_item.production->at(i).symbol);
      }

      description += "  (" + symbol_name(shift_item.lhs());
      for (size_t i = 0; i < shift_item.production->size(); i++) {
        if (i == shift_item.step_index)
          description += "  \u2022";
        description += "  " + symbol_name(shift_item.production->at(i).symbol);
      }
      description += ")";
      description += "\n";
    }

    description += "\nPossible resolutions:\n\n";

    size_t resolution_count = 1;
    if (actual_conflict.size() > 1) {
      if (!shift_items.empty()) {
        description += "  " + to_string(resolution_count++) + ":  ";
        description += "Specify a higher precedence in";
        bool is_first = true;
        for (const ParseItem &shift_item : shift_items) {
          if (!is_first) description += " and";
          description += " `" + symbol_name(shift_item.lhs()) + "`";
          is_first = false;
        }
        description += " than in the other rules.\n";
      }

      for (const ParseAction &action : entry.actions) {
        if (action.type == ParseActionTypeReduce) {
          description += "  " + to_string(resolution_count++) + ":  ";
          description += "Specify a higher precedence in `";
          description += symbol_name(action.symbol);
          description += "` than in the other rules.\n";
        }
      }
    }

    if (considered_associativity) {
      description += "  " + to_string(resolution_count++) + ":  ";
      description += "Specify a left or right associativity in";
      for (const ParseAction &action : entry.actions) {
        bool is_first = true;
        if (action.type == ParseActionTypeReduce) {
          if (!is_first) description += " and";
          description += " `" + symbol_name(action.symbol) + "`";
          is_first = false;
        }
      }
      description += "\n";
    }

    description += "  " + to_string(resolution_count++) + ":  ";
    description += "Add a conflict for these rules:";
    for (const Symbol &conflict_symbol : actual_conflict) {
      description += " `" + symbol_name(conflict_symbol) + "`";
    }
    description += "\n";
    return description;
  }

  string symbol_name(const rules::Symbol &symbol) const {
    if (symbol.is_built_in()) {
      if (symbol == END_OF_INPUT())
        return "END_OF_INPUT";
      else
        return "";
    }

    switch (symbol.type) {
      case Symbol::Terminal: {
        const LexicalVariable &variable = lexical_grammar.variables[symbol.index];
        if (variable.type == VariableTypeNamed)
          return variable.name;
        else
          return "'" + variable.name + "'";
      }
      case Symbol::NonTerminal: {
        return grammar.variables[symbol.index].name;
      }
      case Symbol::External:
      default: {
        return grammar.external_tokens[symbol.index].name;
      }
    }
  }

  bool has_fragile_production(const Production *production) {
    return fragile_productions.find(production) != fragile_productions.end();
  }
};

pair<ParseTable, CompileError> build_parse_table(
  const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
