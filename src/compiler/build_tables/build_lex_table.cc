#include "compiler/build_tables/build_lex_table.h"
#include <climits>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "compiler/build_tables/lex_conflict_manager.h"
#include "compiler/build_tables/remove_duplicate_states.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/parse_table.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/blank.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::set;
using std::string;
using std::vector;
using std::make_shared;
using std::unordered_map;
using rules::Blank;
using rules::Choice;
using rules::CharacterSet;
using rules::Repeat;
using rules::Symbol;
using rules::Metadata;
using rules::Seq;
using rules::MAIN_TOKEN;
using rules::PRECEDENCE;
using rules::IS_ACTIVE;

class LexTableBuilder {
  LexTable lex_table;
  ParseTable *parse_table;
  const LexicalGrammar lex_grammar;
  vector<rule_ptr> separator_rules;
  LexConflictManager conflict_manager;
  unordered_map<const LexItemSet, LexStateId, LexItemSet::Hash> lex_state_ids;

 public:
  LexTableBuilder(ParseTable *parse_table, const LexicalGrammar &lex_grammar)
      : parse_table(parse_table), lex_grammar(lex_grammar) {
    for (const rule_ptr &rule : lex_grammar.separators)
      separator_rules.push_back(Repeat::build(rule));
    separator_rules.push_back(Blank::build());
  }

  LexTable build() {
    for (ParseState &parse_state : parse_table->states)
      add_lex_state_for_parse_state(&parse_state);

    mark_fragile_tokens();
    remove_duplicate_lex_states();

    return lex_table;
  }

 private:
  void add_lex_state_for_parse_state(ParseState *parse_state) {
    parse_state->lex_state_id =
      add_lex_state(item_set_for_tokens(parse_state->expected_inputs()));
  }

  LexStateId add_lex_state(const LexItemSet &item_set) {
    const auto &pair = lex_state_ids.find(item_set);
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

  void add_advance_actions(const LexItemSet &item_set, LexStateId state_id) {
    for (const auto &pair : item_set.transitions()) {
      const CharacterSet &characters = pair.first;
      const LexItemSet::Transition &transition = pair.second;
      AdvanceAction action(-1, transition.precedence, transition.in_main_token);

      auto current_action = lex_table.state(state_id).accept_action;
      if (conflict_manager.resolve(transition.destination, action,
                                   current_action)) {
        action.state_index = add_lex_state(transition.destination);
        lex_table.state(state_id).advance_actions[characters] = action;
      }
    }
  }

  void add_accept_token_actions(const LexItemSet &item_set, LexStateId state_id) {
    for (const LexItem &item : item_set.entries) {
      LexItem::CompletionStatus completion_status = item.completion_status();
      if (completion_status.is_done) {
        AcceptTokenAction action(item.lhs, completion_status.precedence.max,
                                 completion_status.is_string);

        auto current_action = lex_table.state(state_id).accept_action;
        if (conflict_manager.resolve(action, current_action))
          lex_table.state(state_id).accept_action = action;
      }
    }
  }

  void mark_fragile_tokens() {
    for (ParseState &state : parse_table->states) {
      for (auto &entry : state.entries) {
        if (!entry.first.is_token)
          continue;

        auto homonyms = conflict_manager.possible_homonyms.find(entry.first);
        if (homonyms != conflict_manager.possible_homonyms.end())
          for (const Symbol &homonym : homonyms->second)
            if (state.entries.count(homonym)) {
              entry.second.reusable = false;
              break;
            }

        if (!entry.second.reusable)
          continue;

        auto extensions = conflict_manager.possible_extensions.find(entry.first);
        if (extensions != conflict_manager.possible_extensions.end())
          for (const Symbol &extension : extensions->second)
            if (state.entries.count(extension)) {
              entry.second.depends_on_lookahead = true;
              break;
            }
      }
    }
  }

  void remove_duplicate_lex_states() {
    for (LexState &state : lex_table.states) {
      state.accept_action.is_string = false;
      state.accept_action.precedence = 0;
    }

    auto replacements =
      remove_duplicate_states<LexState, AdvanceAction>(&lex_table.states);

    for (ParseState &parse_state : parse_table->states) {
      auto replacement = replacements.find(parse_state.lex_state_id);
      if (replacement != replacements.end())
        parse_state.lex_state_id = replacement->second;
    }
  }

  LexItemSet item_set_for_tokens(const set<Symbol> &symbols) {
    LexItemSet result;
    for (const Symbol &symbol : symbols)
      for (const rule_ptr &rule : rules_for_symbol(symbol))
        for (const rule_ptr &separator_rule : separator_rules)
          result.entries.insert(LexItem(
            symbol,
            Metadata::build(
              Seq::build({
                separator_rule,
                Metadata::build(rule, { { PRECEDENCE, 0 }, { MAIN_TOKEN, 1 } }),
              }),
              { { PRECEDENCE, INT_MIN }, { IS_ACTIVE, true } })));
    return result;
  }

  vector<rule_ptr> rules_for_symbol(const rules::Symbol &symbol) {
    if (!symbol.is_token)
      return {};

    if (symbol == rules::END_OF_INPUT())
      return { CharacterSet().include(0).copy() };

    rule_ptr rule = lex_grammar.variables[symbol.index].rule;

    auto choice = rule->as<Choice>();
    if (choice)
      return choice->elements;
    else
      return { rule };
  }
};

LexTable build_lex_table(ParseTable *table, const LexicalGrammar &grammar) {
  return LexTableBuilder(table, grammar).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
