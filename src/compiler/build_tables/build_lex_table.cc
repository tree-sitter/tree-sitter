#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "compiler/build_tables/action_takes_precedence.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/parse_table.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/seq.h"

namespace tree_sitter {
namespace build_tables {

using std::dynamic_pointer_cast;
using std::make_shared;
using std::map;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;
using rules::CharacterSet;
using rules::Symbol;

class LexTableBuilder {
  const LexicalGrammar lex_grammar;
  ParseTable *parse_table;
  unordered_map<const LexItemSet, LexStateId> lex_state_ids;
  LexTable lex_table;

 public:
  LexTableBuilder(ParseTable *parse_table, const LexicalGrammar &lex_grammar)
      : lex_grammar(lex_grammar), parse_table(parse_table) {}

  LexTable build() {
    for (auto &parse_state : parse_table->states) {
      LexItemSet item_set = build_lex_item_set(parse_state.expected_inputs());
      parse_state.lex_state_id = add_lex_state(item_set);
    }
    add_error_lex_state();
    return lex_table;
  }

 private:
  LexItemSet build_lex_item_set(const set<Symbol> &symbols) {
    LexItemSet result;
    for (const auto &symbol : symbols) {
      if (symbol == rules::ERROR())
        continue;

      if (symbol == rules::END_OF_INPUT())
        result.insert(LexItem(
            symbol, after_separators(CharacterSet().include(0).copy())));

      else if (symbol.is_token())
        result.insert(
            LexItem(symbol, after_separators(lex_grammar.rule(symbol))));
    }
    return result;
  }

  LexStateId add_lex_state(const LexItemSet &item_set) {
    const auto &pair = lex_state_ids.find(item_set);
    if (pair == lex_state_ids.end()) {
      LexStateId state_id = lex_table.add_state();
      lex_state_ids[item_set] = state_id;

      add_accept_token_actions(item_set, state_id);
      add_advance_actions(item_set, state_id);
      add_token_start(item_set, state_id);

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
      if (action_takes_precedence(action,
                                  lex_table.state(state_id).default_action))
        lex_table.state(state_id).actions[rule] = action;
    }
  }

  void add_accept_token_actions(const LexItemSet &item_set, LexStateId state_id) {
    for (const LexItem &item : item_set)
      if (item.is_done()) {
        auto current_action = lex_table.state(state_id).default_action;
        auto new_action = LexAction::Accept(item.lhs, item.precedence());
        if (action_takes_precedence(new_action, current_action))
          lex_table.state(state_id).default_action = new_action;
      }
  }

  void add_token_start(const LexItemSet &item_set, LexStateId state_id) {
    for (const auto &item : item_set)
      if (item.is_token_start())
        lex_table.state(state_id).is_token_start = true;
  }

  rules::rule_ptr after_separators(rules::rule_ptr rule) {
    return rules::Seq::Build(
        { make_shared<rules::Metadata>(
              separator_rule(),
              map<rules::MetadataKey, int>(
                  { { rules::START_TOKEN, 1 }, { rules::PRECEDENCE, -1 }, })),
          rule, });
  }

  rules::rule_ptr separator_rule() const {
    vector<rules::rule_ptr> separators;
    for (const auto &rule : lex_grammar.separators) {

      // TODO - remove this hack. right now, nested repeats cause
      // item sets which are equivalent to appear unequal.
      auto repeat = dynamic_pointer_cast<const rules::Repeat>(rule);
      if (repeat.get())
        separators.push_back(repeat->content);
      else
        separators.push_back(rule);
    }

    return rules::repeat(rules::choice(separators));
  }

  set<int> precedence_values_for_item_set(const LexItemSet &item_set) const {
    set<int> result;
    for (const auto &item : item_set)
      result.insert(item.precedence());
    return result;
  }
};

LexTable build_lex_table(ParseTable *table, const LexicalGrammar &grammar) {
  return LexTableBuilder(table, grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
