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
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

using std::get;
using std::pair;
using std::vector;
using std::set;
using std::map;
using std::string;
using std::unordered_map;
using std::make_shared;
using rules::Symbol;

class ParseTableBuilder {
  const SyntaxGrammar grammar;
  ParseConflictManager conflict_manager;
  unordered_map<const ParseItemSet, ParseStateId> parse_state_ids;
  vector<pair<ParseItemSet, ParseStateId>> item_sets_to_process;
  ParseTable parse_table;
  std::set<string> conflicts;

 public:
  ParseTableBuilder(const SyntaxGrammar &grammar,
                    const LexicalGrammar &lex_grammar)
      : grammar(grammar), conflict_manager(grammar, lex_grammar) {}

  pair<ParseTable, const GrammarError *> build() {
    auto start_symbol = grammar.rules.empty()
                            ? make_shared<Symbol>(0, rules::SymbolOptionToken)
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
      add_shift_extra_actions(state_id);

      if (!conflicts.empty())
        return {
          parse_table,
          new GrammarError(GrammarErrorTypeParseConflict, "Unresolved conflict.\n\n" + *conflicts.begin())
        };
    }

    for (ParseStateId state = 0; state < parse_table.states.size(); state++)
      add_reduce_extra_actions(state);

    parse_table.symbols.insert(rules::ERROR());
    parse_table.symbols.insert(rules::DOCUMENT());

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

      ParseAction new_action =
          ParseAction::Shift(0, precedence_values_for_item_set(next_item_set));
      if (should_add_action(state_id, item_set, symbol, new_action)) {
        ParseStateId new_state_id = add_parse_state(next_item_set);
        new_action.state_index = new_state_id;
        parse_table.add_action(state_id, symbol, new_action);
      }
    }
  }

  void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
    for (const auto &pair : item_set) {
      const ParseItem &item = pair.first;
      const set<Symbol> &lookahead_symbols = pair.second;

      if (item.is_done()) {
        ParseAction action =
            (item.lhs == rules::START())
                ? ParseAction::Accept()
                : ParseAction::Reduce(item.lhs, item.consumed_symbols.size(),
                                      item.precedence(), item.associativity(),
                                      conflict_manager.get_production_id(item.consumed_symbols));

        for (const auto &lookahead_sym : lookahead_symbols)
          if (should_add_action(state_id, item_set, lookahead_sym, action))
            parse_table.add_action(state_id, lookahead_sym, action);
      }
    }
  }

  void add_shift_extra_actions(ParseStateId state_id) {
    const map<Symbol, ParseAction> &actions =
        parse_table.states[state_id].actions;

    for (const Symbol &ubiquitous_symbol : grammar.ubiquitous_tokens) {
      const auto &pair_for_symbol = actions.find(ubiquitous_symbol);
      if (pair_for_symbol == actions.end()) {
        parse_table.add_action(state_id, ubiquitous_symbol,
                               ParseAction::ShiftExtra());
      }
    }
  }

  void add_reduce_extra_actions(ParseStateId state_id) {
    const map<Symbol, ParseAction> &actions =
        parse_table.states[state_id].actions;

    for (const Symbol &ubiquitous_symbol : grammar.ubiquitous_tokens) {
      const auto &pair_for_symbol = actions.find(ubiquitous_symbol);

      if (pair_for_symbol != actions.end() &&
          pair_for_symbol->second.type == ParseActionTypeShift) {
        size_t shift_state_id = pair_for_symbol->second.state_index;
        for (const auto &pair : actions) {
          const Symbol &lookahead_sym = pair.first;
          ParseAction reduce_extra = ParseAction::ReduceExtra(ubiquitous_symbol);
          if (should_add_action(shift_state_id, ParseItemSet(), lookahead_sym, reduce_extra))
            parse_table.add_action(shift_state_id, lookahead_sym, reduce_extra);
        }
      }
    }
  }

  bool should_add_action(ParseStateId state_id, const ParseItemSet &item_set,
                         const Symbol &symbol, const ParseAction &action) {
    auto &current_actions = parse_table.states[state_id].actions;
    auto current_action = current_actions.find(symbol);
    if (current_action == current_actions.end())
      return true;

    auto result = conflict_manager.resolve(action, current_action->second,
                                           symbol, item_set);

    switch (get<1>(result)) {
      case ConflictTypeResolved:
        if (action.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(action.production_id);
        if (current_action->second.type == ParseActionTypeReduce)
          parse_table.fragile_production_ids.insert(current_action->second.production_id);
        break;
      case ConflictTypeError:
        conflicts.insert(get<2>(result));
        break;
      default:
        break;
    }

    return get<0>(result);
  }

  set<int> precedence_values_for_item_set(const ParseItemSet &item_set) {
    set<int> result;
    for (const auto &pair : item_set) {
      const ParseItem &item = pair.first;
      if (!item.consumed_symbols.empty())
        result.insert(item.precedence());
    }
    return result;
  }
};

pair<ParseTable, const GrammarError *> build_parse_table(
    const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  return ParseTableBuilder(grammar, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
