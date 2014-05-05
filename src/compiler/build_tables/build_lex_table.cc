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
#include "compiler/build_tables/first_set.h"

namespace tree_sitter {
    using std::string;
    using std::map;
    using std::unordered_map;
    using std::make_shared;
    using rules::Symbol;
    using rules::CharacterSet;

    namespace build_tables {
        class LexTableBuilder {
            const PreparedGrammar lex_grammar;
            ParseTable *parse_table;
            LexConflictManager conflict_manager;
            unordered_map<const LexItemSet, LexStateId> lex_state_ids;
            LexTable lex_table;

            void add_advance_actions(const LexItemSet &item_set, LexStateId state_id) {
                auto transitions = char_transitions(item_set, lex_grammar);
                for (auto transition : transitions) {
                    CharacterSet rule = transition.first;
                    LexItemSet new_item_set = transition.second;
                    LexStateId new_state_id = add_lex_state(new_item_set);
                    lex_table.add_action(state_id, rule, LexAction::Advance(new_state_id));
                }
            }

            void add_token_start(const LexItemSet &item_set, LexStateId state_id) {
                for (auto &item : item_set)
                    if (item.is_token_start())
                        lex_table.state(state_id).is_token_start = true;
            }

            void add_accept_token_actions(const LexItemSet &item_set, LexStateId state_id) {
                for (LexItem item : item_set) {
                    if (item.is_done()) {
                        auto current_action = lex_table.state(state_id).default_action;
                        auto new_action = LexAction::Accept(item.lhs, item.precedence());
                        if (conflict_manager.resolve_lex_action(current_action, new_action))
                            lex_table.add_default_action(state_id, new_action);
                    }
                }
            }

            rules::rule_ptr after_separators(rules::rule_ptr rule) {
                return rules::Seq::Build({
                    make_shared<rules::Repeat>(CharacterSet({ ' ', '\t', '\n', '\r' }).copy()),
                    make_shared<rules::Metadata>(make_shared<rules::Blank>(), map<rules::MetadataKey, int>({
                        {rules::START_TOKEN, 1},
                    })),
                    rule
                });
            }

            LexItemSet lex_item_set_for_parse_state(const ParseState &state) {
                LexItemSet result;
                for (auto &symbol : state.expected_inputs()) {
                    if (symbol.is_token() && !symbol.is_built_in())
                        result.insert(LexItem(symbol, after_separators(lex_grammar.rule(symbol))));
                    if (symbol == rules::END_OF_INPUT())
                        result.insert(LexItem(symbol, after_separators(CharacterSet({ 0 }).copy())));
                }
                return result;
            }

            void assign_lex_state(ParseState *state) {
                state->lex_state_id = add_lex_state(lex_item_set_for_parse_state(*state));
            }

            LexStateId add_lex_state(const LexItemSet &item_set) {
                auto pair = lex_state_ids.find(item_set);
                if (pair == lex_state_ids.end()) {
                    LexStateId state_id = lex_table.add_state();
                    lex_state_ids[item_set] = state_id;
                    add_token_start(item_set, state_id);
                    add_advance_actions(item_set, state_id);
                    add_accept_token_actions(item_set, state_id);
                    return state_id;
                } else {
                    return pair->second;
                }
            }

            void add_error_lex_state() {
                LexItemSet error_item_set;
                for (size_t i = 0; i < lex_grammar.rules.size(); i++) {
                    LexItem item(Symbol(i, rules::SymbolOptionToken), after_separators(lex_grammar.rules[i].second));
                    error_item_set.insert(item);
                }
                for (size_t i = 0; i < lex_grammar.aux_rules.size(); i++) {
                    LexItem item(Symbol(i, rules::SymbolOption(rules::SymbolOptionToken|rules::SymbolOptionAuxiliary)), after_separators(lex_grammar.aux_rules[i].second));
                    error_item_set.insert(item);
                }
                error_item_set.insert(LexItem(rules::END_OF_INPUT(), after_separators(CharacterSet({ 0 }).copy())));
                add_advance_actions(error_item_set, LexTable::ERROR_STATE_ID);
                add_accept_token_actions(error_item_set, LexTable::ERROR_STATE_ID);
            }

        public:
            LexTableBuilder(ParseTable *parse_table, const PreparedGrammar &lex_grammar) :
                lex_grammar(lex_grammar),
                parse_table(parse_table),
                conflict_manager(LexConflictManager(lex_grammar)) {}

            LexTable build() {
                for (auto &parse_state : parse_table->states)
                    assign_lex_state(&parse_state);
                add_error_lex_state();
                return lex_table;
            }
        };

        LexTable build_lex_table(ParseTable *parse_table, const PreparedGrammar &lex_grammar) {
            return LexTableBuilder(parse_table, lex_grammar).build();
        }
    }
}
