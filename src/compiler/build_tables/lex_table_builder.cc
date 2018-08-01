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
#include "compiler/lexical_grammar.h"
#include "compiler/log.h"
#include "compiler/parse_table.h"
#include "compiler/rule.h"
#include "utf8proc.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::move;
using std::pair;
using std::set;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::unique_ptr;
using std::iswalpha;
using rules::Rule;
using rules::Blank;
using rules::Choice;
using rules::CharacterSet;
using rules::Repeat;
using rules::Symbol;
using rules::Metadata;
using rules::Seq;

bool CoincidentTokenIndex::contains(Symbol a, Symbol b) const {
  return a == b || !states_with(a, b).empty();
}

const unordered_set<ParseStateId> &CoincidentTokenIndex::states_with(Symbol a, Symbol b) const {
  static const unordered_set<ParseStateId> NO_STATES;
  if (a.index > b.index) std::swap(a, b);
  auto iter = entries.find({a.index, b.index});
  if (iter == entries.end()) {
    return NO_STATES;
  } else {
    return iter->second;
  }
}

class LexTableBuilderImpl : public LexTableBuilder {
  enum ConflictStatus {
    DoesNotMatch = 0,
    MatchesShorterStringWithinSeparators = 1 << 0,
    MatchesSameString = 1 << 1,
    MatchesLongerString = 1 << 2,
    MatchesLongerStringWithValidNextChar = 1 << 3,
  };

  LexTable main_lex_table;
  LexTable keyword_lex_table;
  const LexicalGrammar grammar;
  vector<Rule> separator_rules;
  unordered_map<LexItemSet, LexStateId> main_lex_state_ids;
  unordered_map<LexItemSet, LexStateId> keyword_lex_state_ids;
  CharacterSet separator_start_characters;
  vector<CharacterSet> starting_characters_by_token;
  vector<CharacterSet> following_characters_by_token;
  const CoincidentTokenIndex &coincident_token_index;
  ParseTable *parse_table;
  vector<ConflictStatus> conflict_matrix;
  bool conflict_detection_mode;
  LookaheadSet keyword_symbols;
  Symbol word_token;
  char encoding_buffer[8];

 public:
  LexTableBuilderImpl(const SyntaxGrammar &syntax_grammar,
                      const LexicalGrammar &lexical_grammar,
                      const unordered_map<Symbol, LookaheadSet> &following_tokens_by_token,
                      const CoincidentTokenIndex &coincident_token_index,
                      ParseTable *parse_table)
    : grammar(lexical_grammar),
      starting_characters_by_token(lexical_grammar.variables.size()),
      following_characters_by_token(lexical_grammar.variables.size()),
      coincident_token_index(coincident_token_index),
      parse_table(parse_table),
      conflict_matrix(lexical_grammar.variables.size() * lexical_grammar.variables.size(), DoesNotMatch),
      conflict_detection_mode(false),
      word_token(syntax_grammar.word_token) {

    // Compute the possible separator rules and the set of separator characters that can occur
    // immediately after any token.
    for (const auto &rule : grammar.separators) {
      separator_rules.push_back(Repeat{rule});
      add_starting_characters(&separator_start_characters, rule);
    }
    separator_rules.push_back(Blank{});

    // Compute the set of characters that each token can start with and the set of non-separator
    // characters that can follow each token. Also identify all of the tokens that can be
    // considered 'keywords'.
    LOG("characterizing tokens");
    for (unsigned i = 0, n = grammar.variables.size(); i < n; i++) {
      Symbol token = Symbol::terminal(i);

      add_starting_characters(&starting_characters_by_token[i], grammar.variables[i].rule);
      const auto &following_tokens = following_tokens_by_token.find(token);
      if (following_tokens != following_tokens_by_token.end()) {
        following_tokens->second.for_each([&](Symbol following_token) {
          add_starting_characters(
            &following_characters_by_token[i],
            grammar.variables[following_token.index].rule
          );
          return true;
        });
      }
    }

    // For each pair of tokens, generate a lex table for just those two tokens and record what
    // conflicts arise.
    LOG_START("detecting conflicts between tokens");
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
    LOG_END();

    if (word_token != rules::NONE()) identify_keywords();
  }

  void identify_keywords() {
    LookaheadSet homonyms;
    for (Symbol::Index j = 0, n = grammar.variables.size(); j < n; j++) {
      Symbol other_token = Symbol::terminal(j);

      // For now, only consider tokens as 'keywords' if they start with letters or underscores.
      bool starts_with_letter = !starting_characters_by_token[j].includes_all;
      for (auto character : starting_characters_by_token[j].included_chars) {
        if (!iswalpha(character) && character != '_') {
          starts_with_letter = false;
          break;
        }
      }
      if (!starts_with_letter) continue;

      if (get_conflict_status(word_token, other_token) == MatchesSameString) {
        homonyms.insert(other_token);
      }
    }

    homonyms.for_each([&](Symbol homonym1) {
      homonyms.for_each([&](Symbol homonym2) {
        if (get_conflict_status(homonym1, homonym2) & MatchesSameString) {
          LOG(
            "conflict between homonyms %s %s",
            token_name(homonym1).c_str(),
            token_name(homonym2).c_str()
          );
          homonyms.remove(homonym1);
        }
        return false;
      });
      return true;
    });

    for (Symbol::Index j = 0, n = grammar.variables.size(); j < n; j++) {
      Symbol other_token = Symbol::terminal(j);
      if (other_token == word_token || homonyms.contains(other_token)) continue;
      bool word_rule_shadows_other = get_conflict_status(other_token, word_token);
      bool other_shadows_word_rule = get_conflict_status(word_token, other_token);

      if (word_rule_shadows_other || other_shadows_word_rule) {
        homonyms.for_each([&](Symbol homonym) {
          bool word_rule_was_already_present = true;
          for (ParseStateId state_id : coincident_token_index.states_with(homonym, other_token)) {
            if (!parse_table->states[state_id].has_terminal_entry(word_token)) {
              word_rule_was_already_present = false;
              break;
            }
          }
          if (word_rule_was_already_present) return true;

          bool homonym_shadows_other = get_conflict_status(other_token, homonym);
          bool other_shadows_homonym = get_conflict_status(homonym, other_token);

          if (word_rule_shadows_other != homonym_shadows_other) {
            homonyms.remove(homonym);
            LOG(
              "remove %s because word_token would shadow %s",
              token_name(homonym).c_str(),
              token_name(other_token).c_str()
            );
          } else if (other_shadows_word_rule != other_shadows_homonym) {
            homonyms.remove(homonym);
            LOG(
              "remove %s because %s would shadow word_token",
              token_name(homonym).c_str(),
              token_name(other_token).c_str()
            );
          }
          return true;
        });
      }
    }

    if (!homonyms.empty()) {
      LOG_START("found keywords:");
      homonyms.for_each([&](Symbol homonym) {
        LOG("%s", token_name(homonym).c_str());
        return true;
      });
      LOG_END();
      keyword_symbols = homonyms;
    }
  }

  BuildResult build() {
    clear();
    conflict_detection_mode = false;
    vector<pair<LookaheadSet, vector<ParseState *>>> starting_token_sets;

    for (ParseState &parse_state : parse_table->states) {
      LookaheadSet token_set;
      for (auto &entry : parse_state.terminal_entries) {
        if (word_token.is_terminal() && keyword_symbols.contains(entry.first)) {
          token_set.insert(word_token);
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

    mark_fragile_tokens();
    remove_duplicate_lex_states(main_lex_table);
    return {main_lex_table, keyword_lex_table, word_token};
  }

  bool does_token_shadow_other(Symbol token, Symbol shadowed_token) const {
    if (keyword_symbols.contains(shadowed_token) &&
        (keyword_symbols.contains(token) || token == word_token)) return false;
    return get_conflict_status(shadowed_token, token) & (
      MatchesShorterStringWithinSeparators |
      MatchesLongerStringWithValidNextChar
    );
  }

  bool does_token_match_same_string_as_other(Symbol token, Symbol shadowed_token) const {
    if (shadowed_token == word_token && keyword_symbols.contains(token)) return false;
    return get_conflict_status(shadowed_token, token) & MatchesSameString;
  }

 private:
  ConflictStatus get_conflict_status(Symbol shadowed_token, Symbol other_token) const {
    if (shadowed_token.is_built_in() ||
        other_token.is_built_in() ||
        !shadowed_token.is_terminal() ||
        !other_token.is_terminal()) return DoesNotMatch;
    unsigned index = shadowed_token.index * grammar.variables.size() + other_token.index;
    return conflict_matrix[index];
  }

  bool record_conflict(Symbol shadowed_token, Symbol other_token, ConflictStatus status) {
    if (!conflict_detection_mode) return false;
    unsigned index = shadowed_token.index * grammar.variables.size() + other_token.index;
    bool was_set = conflict_matrix[index] & status;
    conflict_matrix[index] = static_cast<ConflictStatus>(conflict_matrix[index] | status);
    return !was_set;
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
            auto &following_chars = following_characters_by_token[accept_action.symbol.index];
            CharacterSet conflicting_following_chars = characters.intersection(following_chars);
            if (conflicting_following_chars.is_empty()) {
              conflicting_following_chars = characters.intersection(separator_start_characters);
            }
            if (conflicting_following_chars.is_empty()) {
              record_conflict(accept_action.symbol, advance_symbol, MatchesLongerString);
            } else {
              if (record_conflict(
                accept_action.symbol,
                advance_symbol,
                MatchesLongerStringWithValidNextChar
              )) {
                if (!conflicting_following_chars.included_chars.empty()) {
                  LOG(
                    "%s shadows %s followed by '%s'",
                    token_name(advance_symbol).c_str(),
                    token_name(accept_action.symbol).c_str(),
                    log_char(*conflicting_following_chars.included_chars.begin())
                  );
                }
              }
            }
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
        AcceptTokenAction action(item.lhs, completion_status.precedence.max);

        if (!item.lhs.is_built_in()) {
          const LexicalVariable &variable = grammar.variables[item.lhs.index];
          if (variable.is_string) action.implicit_precedence += 2;
          if (is_immediate_token(variable.rule)) action.implicit_precedence += 1;
        }

        AcceptTokenAction &existing_action = lex_table.states[state_id].accept_action;
        if (existing_action.is_present()) {
          if (should_replace_accept_action(existing_action, action)) {
            if (record_conflict(existing_action.symbol, action.symbol, MatchesSameString)) {
              LOG(
                "%s shadows %s - same length",
                token_name(action.symbol).c_str(),
                token_name(existing_action.symbol).c_str()
              );
            }
          } else {
            if (record_conflict(action.symbol, existing_action.symbol, MatchesSameString)) {
              LOG(
                "%s shadows %s - same length",
                token_name(existing_action.symbol).c_str(),
                token_name(action.symbol).c_str()
              );
            }
            continue;
          }
        }
        lex_table.states[state_id].accept_action = action;
      }
    }
  }

  void mark_fragile_tokens() {
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
    auto CannotDistinguish = (
      MatchesShorterStringWithinSeparators |
      MatchesSameString |
      MatchesLongerStringWithValidNextChar
    );

    bool is_compatible = true;

    left->for_each_difference(right, [&](bool in_left, Symbol different_symbol) {
      if (!different_symbol.is_external() && !different_symbol.is_built_in()) {
        const LookaheadSet &existing_set = in_left ? right : *left;
        existing_set.for_each([&](Symbol existing_symbol) {
          if ((get_conflict_status(existing_symbol, different_symbol) & CannotDistinguish) ||
              !coincident_token_index.contains(different_symbol, existing_symbol)) {
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

  void remove_duplicate_lex_states(LexTable &lex_table) {
    for (LexState &state : lex_table.states) {
      state.accept_action.precedence = 0;
      state.accept_action.implicit_precedence = 0;
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

  bool is_immediate_token(const Rule &rule) const {
    return rule.match(
      [](const Metadata &metadata) {
        return metadata.params.is_main_token;
      },

      [](auto rule) {
        return false;
      }
    );
  }

  LexItemSet item_set_for_terminals(const LookaheadSet &terminals, bool with_separators) {
    LexItemSet result;
    terminals.for_each([&](Symbol symbol) {
      if (symbol.is_terminal()) {
        for (auto &&rule : rules_for_symbol(symbol)) {
          if (with_separators && !is_immediate_token(rule)) {
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

  static void add_starting_characters(CharacterSet *characters, const Rule &rule) {
    rule.match(
      [characters](const Seq &sequence) {
        add_starting_characters(characters, *sequence.left);
      },

      [characters](const rules::Choice &rule) {
        for (const auto &element : rule.elements) {
          add_starting_characters(characters, element);
        }
      },

      [characters](const rules::Repeat &rule) {
        add_starting_characters(characters, *rule.rule);
      },

      [characters](const rules::Metadata &rule) {
        add_starting_characters(characters, *rule.rule);
      },

      [characters](const rules::CharacterSet &rule) {
        characters->add_set(rule);
      },

      [](auto) {}
    );
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
    if (new_action.implicit_precedence > old_action.implicit_precedence) return true;
    if (new_action.implicit_precedence < old_action.implicit_precedence) return false;
    return new_action.symbol.index < old_action.symbol.index;
  }

  void clear() {
    main_lex_table.states.clear();
    main_lex_state_ids.clear();
  }

  string token_name(const rules::Symbol &symbol) {
    const LexicalVariable &variable = grammar.variables[symbol.index];
    if (variable.type == VariableTypeNamed) {
      return variable.name;
    } else {
      return "'" + variable.name + "'";
    }
  }

  const char *log_char(int32_t character) {
    uint32_t count = utf8proc_encode_char(
      character,
      reinterpret_cast<utf8proc_uint8_t *>(encoding_buffer)
    );
    encoding_buffer[count] = 0;
    return encoding_buffer;
  }
};

unique_ptr<LexTableBuilder> LexTableBuilder::create(const SyntaxGrammar &syntax_grammar,
                                                    const LexicalGrammar &lexical_grammar,
                                                    const unordered_map<Symbol, LookaheadSet> &following_tokens,
                                                    const CoincidentTokenIndex &coincident_tokens,
                                                    ParseTable *parse_table) {
  return unique_ptr<LexTableBuilder>(new LexTableBuilderImpl(
    syntax_grammar,
    lexical_grammar,
    following_tokens,
    coincident_tokens,
    parse_table
  ));
}

LexTableBuilder::BuildResult LexTableBuilder::build() {
  return static_cast<LexTableBuilderImpl *>(this)->build();
}

bool LexTableBuilder::does_token_shadow_other(Symbol a, Symbol b) const {
  return static_cast<const LexTableBuilderImpl *>(this)->does_token_shadow_other(a, b);
}

bool LexTableBuilder::does_token_match_same_string_as_other(Symbol a, Symbol b) const {
  return static_cast<const LexTableBuilderImpl *>(this)->does_token_match_same_string_as_other(a, b);
}

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::rules::Symbol;

size_t hash<pair<Symbol::Index, Symbol::Index>>::operator()(
  const pair<Symbol::Index, Symbol::Index> &p
) const {
  hash<Symbol::Index> hasher;
  return hasher(p.first) ^ hasher(p.second);
}

} // namespace std
