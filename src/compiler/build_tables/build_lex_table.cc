#include "compiler/build_tables/build_tables.h"
#include <string>
#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/seq.h"
#include "compiler/build_tables/lex_conflict_manager.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/item_set_transitions.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::map;
using std::unordered_map;
using std::set;
using std::make_shared;
using rules::Symbol;
using rules::CharacterSet;

class LexTableBuilder {
  const LexicalGrammar lex_grammar;
  ParseTable *parse_table;
  LexConflictManager conflict_manager;
  unordered_map<const LexItemSet, LexStateId> lex_state_ids;
  LexTable lex_table;

  LexItemSet build_lex_item_set(const set<Symbol> &symbols) {
    LexItemSet result;
    for (const auto &symbol : symbols) {
      if (symbol == rules::ERROR())
        continue;
      else if (symbol == rules::END_OF_INPUT())
        result.insert(LexItem(symbol, CharacterSet().include(0).copy()));
      else if (symbol.is_token())
        result.insert(LexItem(symbol, lex_grammar.rule(symbol)));
    }
    return result;
  }

  LexStateId add_lex_state(const LexItemSet &item_set) {
    auto pair = lex_state_ids.find(item_set);
    if (pair == lex_state_ids.end()) {
      LexStateId state_id = lex_table.add_state();
      lex_state_ids[item_set] = state_id;

      add_accept_token_actions(item_set, state_id);
      add_advance_actions(item_set, state_id);

      return state_id;
    } else {
      return pair->second;
    }
  }

  void add_error_lex_state() {
    LexItemSet item_set = build_lex_item_set(parse_table->symbols);
    add_accept_token_actions(item_set, LexTable::ERROR_STATE_ID);
    add_advance_actions(item_set, LexTable::ERROR_STATE_ID);
  }

  void add_advance_actions(const LexItemSet &item_set, LexStateId state_id) {
    auto transitions = char_transitions(item_set);
    for (const auto &transition : transitions) {
      CharacterSet rule = transition.first;
      LexItemSet new_item_set = transition.second;
      LexStateId new_state_id = add_lex_state(new_item_set);
      auto action = LexAction::Advance(
          new_state_id, precedence_values_for_item_set(new_item_set));
      if (conflict_manager.resolve_lex_action(
              lex_table.state(state_id).default_action, action))
        lex_table.state(state_id).actions[rule] = action;
    }
  }

  void add_accept_token_actions(const LexItemSet &item_set,
                                LexStateId state_id) {
    for (const LexItem &item : item_set) {
      if (item.is_done()) {
        auto current_action = lex_table.state(state_id).default_action;
        auto new_action = LexAction::Accept(item.lhs, item.precedence());
        if (conflict_manager.resolve_lex_action(current_action, new_action))
          lex_table.state(state_id).default_action = new_action;
      }
    }
  }

  set<int> precedence_values_for_item_set(const LexItemSet &item_set) const {
    set<int> result;
    for (const auto &item : item_set)
      result.insert(item.precedence());
    return result;
  }

 public:
  LexTableBuilder(ParseTable *parse_table, const LexicalGrammar &lex_grammar)
      : lex_grammar(lex_grammar),
        parse_table(parse_table),
        conflict_manager(LexConflictManager(lex_grammar)) {}

  LexTable build() {
    for (auto &parse_state : parse_table->states) {
      LexItemSet item_set = build_lex_item_set(parse_state.expected_inputs());
      parse_state.lex_state_id = add_lex_state(item_set);
    }
    add_error_lex_state();
    return lex_table;
  }
};

LexTable build_lex_table(ParseTable *parse_table,
                         const LexicalGrammar &lex_grammar) {
  return LexTableBuilder(parse_table, lex_grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
