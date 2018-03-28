#include "compiler/build_tables/lex_table_builder.h"
#include <climits>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <cwctype>
#include <vector>
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/parse_table.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

using std::iswalpha;
using std::map;
using std::move;
using std::pair;
using std::set;
using std::string;
using std::vector;
using std::unordered_map;
using std::unique_ptr;
using rules::Rule;
using rules::Blank;
using rules::Choice;
using rules::CharacterSet;
using rules::Repeat;
using rules::Symbol;
using rules::Metadata;
using rules::Seq;

template <bool include_all>
class StartOrEndCharacterAggregator {
 public:
  void apply(const Rule &rule) {
    rule.match(
      [this](const Seq &sequence) {
        apply(*sequence.left);
        if (include_all) apply(*sequence.right);
      },

      [this](const rules::Choice &rule) {
        for (const auto &element : rule.elements) {
          apply(element);
        }
      },

      [this](const rules::Repeat &rule) { apply(*rule.rule); },
      [this](const rules::Metadata &rule) { apply(*rule.rule); },
      [this](const rules::CharacterSet &rule) { result.add_set(rule); },
      [](auto) {}
    );
  }

  CharacterSet result;
};

using StartingCharacterAggregator = StartOrEndCharacterAggregator<false>;
using AllCharacterAggregator = StartOrEndCharacterAggregator<true>;

class LexTableBuilderImpl : public LexTableBuilder {
  LexTable main_lex_table;
  LexTable keyword_lex_table;
  const LexicalGrammar grammar;
  vector<Rule> separator_rules;
  unordered_map<LexItemSet, LexStateId> main_lex_state_ids;
  unordered_map<LexItemSet, LexStateId> keyword_lex_state_ids;
  CharacterSet separator_start_characters;
  vector<CharacterSet> starting_characters_by_token;
  vector<CharacterSet> following_characters_by_token;
  const vector<LookaheadSet> &coincident_tokens_by_token;
  vector<ConflictStatus> conflict_matrix;
  bool conflict_detection_mode;
  LookaheadSet keyword_symbols;
  Symbol keyword_capture_token;

 public:
  LexTableBuilderImpl(const SyntaxGrammar &syntax_grammar,
                      const LexicalGrammar &lexical_grammar,
                      const unordered_map<Symbol, LookaheadSet> &following_tokens_by_token,
                      const vector<LookaheadSet> &coincident_tokens)
    : grammar(lexical_grammar),
      starting_characters_by_token(lexical_grammar.variables.size()),
      following_characters_by_token(lexical_grammar.variables.size()),
      coincident_tokens_by_token(coincident_tokens),
      conflict_matrix(lexical_grammar.variables.size() * lexical_grammar.variables.size(), DoesNotMatch),
      conflict_detection_mode(false),
      keyword_capture_token(rules::NONE()) {

    // Compute the possible separator rules and the set of separator characters that can occur
    // immediately after any token.
    StartingCharacterAggregator separator_character_aggregator;
    for (const auto &rule : grammar.separators) {
      separator_rules.push_back(Repeat{rule});
      separator_character_aggregator.apply(rule);
    }
    separator_rules.push_back(Blank{});
    separator_start_characters = separator_character_aggregator.result;

    // Compute the set of characters that each token can start with and the set of non-separator
    // characters that can follow each token.
    for (unsigned i = 0, n = grammar.variables.size(); i < n; i++) {
      StartingCharacterAggregator starting_character_aggregator;
      starting_character_aggregator.apply(grammar.variables[i].rule);
      starting_characters_by_token[i] = starting_character_aggregator.result;

      StartingCharacterAggregator following_character_aggregator;
      const auto &following_tokens = following_tokens_by_token.find(Symbol::terminal(i));
      if (following_tokens != following_tokens_by_token.end()) {
        following_tokens->second.for_each([&](Symbol following_token) {
          following_character_aggregator.apply(grammar.variables[following_token.index].rule);
          return true;
        });
      }

      if (grammar.variables[i].is_string) {
        AllCharacterAggregator aggregator;
        aggregator.apply(grammar.variables[i].rule);
        bool all_alpha = true, all_lower = true;
        for (auto character : aggregator.result.included_chars) {
          if (!iswalpha(character) && character != '_') all_alpha = false;
          if (!iswlower(character)) all_lower = false;
        }

        if (all_lower) {
          keyword_symbols.insert(Symbol::terminal(i));
        }

        // TODO - Refactor this. In general, a keyword token cannot be followed immediately
        // by another alphanumeric character. But this requirement is currently not expressed
        // anywhere in the grammar. So without this hack, we would be overly conservative about
        // merging parse states because we would often consider `identifier` tokens to *conflict*
        // with keyword tokens.
        if (all_alpha) {
          following_character_aggregator.result
            .exclude('a', 'z')
            .exclude('A', 'Z')
            .exclude('0', '9')
            .exclude('_')
            .exclude('$');
        }
      }

      following_characters_by_token[i] = following_character_aggregator.result;
    }

    // For each pair of tokens, generate a lex table for just those two tokens and record what
    // conflicts arise.
    conflict_detection_mode = true;
    for (Symbol::Index i = 0, n = grammar.variables.size(); i < n; i++) {
      for (Symbol::Index j = 0; j < i; j++) {
        if (starting_characters_by_token[i].intersects(starting_characters_by_token[j]) ||
            starting_characters_by_token[i].intersects(separator_start_characters) ||
            starting_characters_by_token[j].intersects(separator_start_characters)) {
          clear();
          add_lex_state(main_lex_table, item_set_for_terminals(LookaheadSet({
            Symbol::terminal(i),
            Symbol::terminal(j)
          }), true));
        }
      }
    }

    // Find a 'keyword capture token' that matches all of the indentified keywords.
    for (Symbol::Index i = 0, n = grammar.variables.size(); i < n; i++) {
      Symbol symbol = Symbol::terminal(i);
      bool matches_all_keywords = true;
      keyword_symbols.for_each([&](Symbol keyword_symbol) {
        if (!(get_conflict_status(symbol, keyword_symbol) & MatchesSameString)) {
          matches_all_keywords = false;
          return false;
        }
        return true;
      });
      if (!matches_all_keywords) continue;

      // Don't use a token to capture keywords if it overlaps with separator characters.
      AllCharacterAggregator capture_aggregator;
      capture_aggregator.apply(grammar.variables[i].rule);
      if (capture_aggregator.result.includes_all) continue;
      if (capture_aggregator.result.intersects(separator_start_characters)) continue;

      // Don't use a token to capture keywords if it conflicts with other tokens
      // that occur in the same state as a keyword.
      bool shadows_other_tokens = false;
      for (Symbol::Index j = 0; j < n; j++) {
        Symbol other_symbol = Symbol::terminal(j);
        if ((get_conflict_status(other_symbol, symbol) & (MatchesShorterStringWithinSeparators|MatchesLongerStringWithValidNextChar)) &&
            !keyword_symbols.contains(other_symbol) &&
            keyword_symbols.intersects(coincident_tokens_by_token[j])) {
          shadows_other_tokens = true;
          break;
        }
      }
      if (shadows_other_tokens) continue;

      // If multiple keyword capture tokens are found, don't bother extracting
      // the keywords into their own function.
      if (keyword_capture_token == rules::NONE()) {
        keyword_capture_token = symbol;
      } else {
        keyword_capture_token = rules::NONE();
        break;
      }
    }
  }

  BuildResult build(ParseTable *parse_table) {
    clear();
    conflict_detection_mode = false;
    vector<pair<LookaheadSet, vector<ParseState *>>> starting_token_sets;

    for (ParseState &parse_state : parse_table->states) {
      LookaheadSet token_set;
      for (auto &entry : parse_state.terminal_entries) {
        if (keyword_capture_token.is_terminal() && keyword_symbols.contains(entry.first)) {
          token_set.insert(keyword_capture_token);
        } else {
          token_set.insert(entry.first);
        }
      }

      bool did_merge = false;
      for (auto &pair : starting_token_sets) {
        if (merge_token_set(&pair.first, token_set)) {
          did_merge = true;
          pair.second.push_back(&parse_state);
          break;
        }
      }

      if (!did_merge) starting_token_sets.push_back({token_set, {&parse_state}});
    }

    for (auto &pair : starting_token_sets) {
      LexStateId state_id = add_lex_state(main_lex_table, item_set_for_terminals(pair.first, true));
      for (ParseState *parse_state : pair.second) {
        parse_state->lex_state_id = state_id;
      }
    }

    add_lex_state(keyword_lex_table, item_set_for_terminals(keyword_symbols, false));

    mark_fragile_tokens(parse_table);
    remove_duplicate_lex_states(main_lex_table, parse_table);
    return {main_lex_table, keyword_lex_table, keyword_capture_token};
  }

  ConflictStatus get_conflict_status(Symbol shadowed_token, Symbol other_token) const {
    if (shadowed_token.is_built_in() ||
        other_token.is_built_in() ||
        !shadowed_token.is_terminal() ||
        !other_token.is_terminal()) return DoesNotMatch;
    unsigned index = shadowed_token.index * grammar.variables.size() + other_token.index;
    return conflict_matrix[index];
  }

 private:
  void record_conflict(Symbol shadowed_token, Symbol other_token, ConflictStatus status) {
    unsigned index = shadowed_token.index * grammar.variables.size() + other_token.index;
    conflict_matrix[index] = static_cast<ConflictStatus>(conflict_matrix[index] | status);
  }

  LexStateId add_lex_state(LexTable &lex_table, const LexItemSet &item_set) {
    auto &lex_state_ids = &lex_table == &main_lex_table ?
      main_lex_state_ids :
      keyword_lex_state_ids;
    const auto &pair = lex_state_ids.find(item_set);
    if (pair == lex_state_ids.end()) {
      LexStateId state_id = lex_table.states.size();
      lex_table.states.push_back(LexState());
      lex_state_ids[item_set] = state_id;
      add_accept_token_actions(lex_table, item_set, state_id);
      add_advance_actions(lex_table, item_set, state_id);
      return state_id;
    } else {
      return pair->second;
    }
  }

  void add_advance_actions(LexTable &lex_table, const LexItemSet &item_set, LexStateId state_id) {
    for (const auto &pair : item_set.transitions()) {
      const CharacterSet &characters = pair.first;
      const LexItemSet::Transition &transition = pair.second;

      AdvanceAction action(-1, transition.precedence, transition.in_main_token);
      AcceptTokenAction &accept_action = lex_table.states[state_id].accept_action;
      if (accept_action.is_present()) {
        bool prefer_advancing = action.precedence_range.max >= accept_action.precedence;

        if (conflict_detection_mode) {
          bool next_item_set_can_yield_this_token = false;
          for (const LexItem &item : transition.destination.entries) {
            if (item.lhs == accept_action.symbol) {
              next_item_set_can_yield_this_token = true;
            } else if (!prefer_advancing && item_set.has_items_in_separators()) {
              record_conflict(item.lhs, accept_action.symbol, MatchesShorterStringWithinSeparators);
            }
          }

          if (prefer_advancing && !next_item_set_can_yield_this_token) {
            auto advance_symbol = transition.destination.entries.begin()->lhs;
            if (characters.intersects(following_characters_by_token[accept_action.symbol.index]) ||
                characters.intersects(separator_start_characters)) {
              record_conflict(accept_action.symbol, advance_symbol, MatchesLongerStringWithValidNextChar);
            } else {
              record_conflict(accept_action.symbol, advance_symbol, MatchesLongerString);
            }
            return;
          }
        }

        if (!prefer_advancing) continue;
      }

      action.state_index = add_lex_state(lex_table, transition.destination);
      lex_table.states[state_id].advance_actions[characters] = action;
    }
  }

  void add_accept_token_actions(LexTable &lex_table, const LexItemSet &item_set, LexStateId state_id) {
    for (const LexItem &item : item_set.entries) {
      LexItem::CompletionStatus completion_status = item.completion_status();
      if (completion_status.is_done) {
        AcceptTokenAction action(item.lhs, completion_status.precedence.max,
                                 item.lhs.is_built_in() ||
                                 grammar.variables[item.lhs.index].is_string);
        AcceptTokenAction &existing_action = lex_table.states[state_id].accept_action;
        if (existing_action.is_present()) {
          if (should_replace_accept_action(existing_action, action)) {
            record_conflict(existing_action.symbol, action.symbol, MatchesSameString);
          } else {
            record_conflict(action.symbol, existing_action.symbol, MatchesSameString);
            continue;
          }
        }
        lex_table.states[state_id].accept_action = action;
      }
    }
  }

  void mark_fragile_tokens(ParseTable *parse_table) {
    for (ParseState &state : parse_table->states) {
      for (auto &entry : state.terminal_entries) {
        Symbol token = entry.first;
        if (token.is_external() || token.is_built_in()) continue;
        for (unsigned i = 0; i < grammar.variables.size(); i++) {
          Symbol other_token = Symbol::terminal(i);
          ConflictStatus status = get_conflict_status(token, other_token);
          if (status != ConflictStatus::DoesNotMatch &&
              state.terminal_entries.count(other_token)) {
            entry.second.reusable = false;
            break;
          }
        }
      }
    }
  }

  bool merge_token_set(LookaheadSet *left, const LookaheadSet &right) const {
    bool is_compatible = true;

    left->for_each_difference(right, [&](bool in_left, Symbol different_symbol) {
      if (!different_symbol.is_external() && !different_symbol.is_built_in()) {
        const LookaheadSet &existing_set = in_left ? right : *left;
        existing_set.for_each([&](Symbol existing_symbol) {
          if ((get_conflict_status(existing_symbol, different_symbol) & CannotDistinguish) ||
              !coincident_tokens_by_token[different_symbol.index].contains(existing_symbol)) {
            is_compatible = false;
            return false;
          }
          return true;
        });
        if (!is_compatible) return false;
      }

      return true;
    });

    if (is_compatible) left->insert_all(right);
    return is_compatible;
  }

  void remove_duplicate_lex_states(LexTable &lex_table, ParseTable *parse_table) {
    for (LexState &state : lex_table.states) {
      state.accept_action.is_string = false;
      state.accept_action.precedence = 0;
    }

    map<LexStateId, LexStateId> replacements;

    while (true) {
      map<LexStateId, LexStateId> duplicates;
      for (LexStateId i = 0, size = lex_table.states.size(); i < size; i++) {
        for (LexStateId j = 0; j < i; j++) {
          if (!duplicates.count(j) && lex_table.states[j] == lex_table.states[i]) {
            duplicates.insert({ i, j });
            break;
          }
        }
      }

      if (duplicates.empty()) break;

      map<LexStateId, LexStateId> new_replacements;
      for (LexStateId i = 0, size = lex_table.states.size(); i < size; i++) {
        LexStateId new_state_index = i;
        auto duplicate = duplicates.find(i);
        if (duplicate != duplicates.end()) {
          new_state_index = duplicate->second;
        }

        size_t prior_removed = 0;
        for (const auto &duplicate : duplicates) {
          if (duplicate.first >= new_state_index) break;
          prior_removed++;
        }

        new_state_index -= prior_removed;
        new_replacements.insert({i, new_state_index});
        replacements.insert({ i, new_state_index });
        for (auto &replacement : replacements) {
          if (replacement.second == i) {
            replacement.second = new_state_index;
          }
        }
      }

      for (auto &state : lex_table.states) {
        for (auto &entry : state.advance_actions) {
          auto new_replacement = new_replacements.find(entry.second.state_index);
          if (new_replacement != new_replacements.end()) {
            entry.second.state_index = new_replacement->second;
          }
        }
      }

      for (auto i = duplicates.rbegin(); i != duplicates.rend(); ++i) {
        lex_table.states.erase(lex_table.states.begin() + i->first);
      }
    }

    for (ParseState &parse_state : parse_table->states) {
      auto replacement = replacements.find(parse_state.lex_state_id);
      if (replacement != replacements.end()) {
        parse_state.lex_state_id = replacement->second;
      }
    }
  }

  LexItemSet item_set_for_terminals(const LookaheadSet &terminals, bool with_separators) {
    LexItemSet result;
    terminals.for_each([&](Symbol symbol) {
      if (symbol.is_terminal()) {
        for (auto &&rule : rules_for_symbol(symbol)) {
          if (with_separators) {
            for (const auto &separator_rule : separator_rules) {
              result.entries.insert(LexItem(
                symbol,
                Metadata::separator(
                  Rule::seq({
                    separator_rule,
                    Metadata::main_token(move(rule))
                  })
                )
              ));
            }
          } else {
           result.entries.insert(LexItem(symbol, Metadata::main_token(move(rule))));
         }
        }
      }
      return true;
    });
    return result;
  }

  vector<Rule> rules_for_symbol(const rules::Symbol &symbol) {
    if (symbol == rules::END_OF_INPUT()) {
      return { CharacterSet().include(0) };
    }

    return grammar.variables[symbol.index].rule.match(
      [](const Choice &choice) {
        return choice.elements;
      },

      [](auto rule) {
        return vector<Rule>{ rule };
      }
    );
  }

  bool should_replace_accept_action(const AcceptTokenAction &old_action,
                                    const AcceptTokenAction &new_action) {
    if (new_action.precedence > old_action.precedence) return true;
    if (new_action.precedence < old_action.precedence) return false;
    if (new_action.is_string && !old_action.is_string) return true;
    if (old_action.is_string && !new_action.is_string) return false;
    return new_action.symbol.index < old_action.symbol.index;
  }

  void clear() {
    main_lex_table.states.clear();
    main_lex_state_ids.clear();
  }

  const string &token_name(rules::Symbol &symbol) {
    return grammar.variables[symbol.index].name;
  }
};

unique_ptr<LexTableBuilder> LexTableBuilder::create(const SyntaxGrammar &syntax_grammar,
                                                    const LexicalGrammar &lexical_grammar,
                                                    const unordered_map<Symbol, LookaheadSet> &following_tokens,
                                                    const vector<LookaheadSet> &coincident_tokens) {
  return unique_ptr<LexTableBuilder>(new LexTableBuilderImpl(
    syntax_grammar,
    lexical_grammar,
    following_tokens,
    coincident_tokens
  ));
}

LexTableBuilder::BuildResult LexTableBuilder::build(ParseTable *parse_table) {
  return static_cast<LexTableBuilderImpl *>(this)->build(parse_table);
}

ConflictStatus LexTableBuilder::get_conflict_status(Symbol a, Symbol b) const {
  return static_cast<const LexTableBuilderImpl *>(this)->get_conflict_status(a, b);
}

}  // namespace build_tables
}  // namespace tree_sitter
