#include "compiler/build_tables/build_tables.h"
#include <string>
#include <utility>
#include <map>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/build_tables/item.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/build_tables/first_set.h"

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::map;
    using std::make_shared;
    using rules::Symbol;
    using rules::CharacterSet;

    namespace build_tables {
        const int NOT_FOUND = -2;

        class TableBuilder {
            const PreparedGrammar grammar;
            const PreparedGrammar lex_grammar;
            map<const ParseItemSet, ParseStateId> parse_state_ids;
            map<const LexItemSet, LexStateId> lex_state_ids;
            ParseTable parse_table;
            LexTable lex_table;

            int64_t parse_state_id_for_item_set(const ParseItemSet &item_set) const {
                auto entry = parse_state_ids.find(item_set);
                return (entry == parse_state_ids.end()) ? NOT_FOUND : entry->second;
            }

            int64_t lex_state_id_for_item_set(const LexItemSet &item_set) const {
                auto entry = lex_state_ids.find(item_set);
                return (entry == lex_state_ids.end()) ? NOT_FOUND : entry->second;
            }

            void add_shift_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (auto transition : sym_transitions(item_set, grammar)) {
                    Symbol symbol = transition.first;
                    ParseItemSet item_set = transition.second;
                    ParseStateId new_state_id = add_parse_state(item_set);
                    parse_table.add_action(state_id, symbol, ParseAction::Shift(new_state_id));

                    if (symbol == rules::ERROR) {
                        parse_table.error_table.insert({ state_id, { new_state_id, first_set(transition.second, grammar) } });
                    }
                }
            }

            void add_advance_actions(const LexItemSet &item_set, LexStateId state_id) {
                for (auto transition : char_transitions(item_set, grammar)) {
                    CharacterSet rule = transition.first;
                    LexItemSet item_set = transition.second;
                    LexStateId new_state_id = add_lex_state(item_set);
                    lex_table.add_action(state_id, rule, LexAction::Advance(new_state_id));
                }
            }

            void add_accept_token_actions(const LexItemSet &item_set, LexStateId state_id) {
                for (LexItem item : item_set) {
                    if (item.is_done()) {
                        lex_table.add_default_action(state_id, LexAction::Accept(item.lhs));
                    }
                }
            }

            void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (ParseItem item : item_set) {
                    if (item.is_done()) {
                        ParseAction action = (item.lhs == rules::START) ?
                            ParseAction::Accept() :
                            ParseAction::Reduce(item.lhs, item.consumed_symbols);
                        parse_table.add_action(state_id, item.lookahead_sym, action);
                    }
                }
            }

            void assign_lex_state(ParseStateId state_id) {
                ParseState &state = parse_table.states[state_id];
                LexItemSet item_set;
                for (auto &symbol : state.expected_inputs()) {
                    if (lex_grammar.has_definition(symbol))
                        item_set.insert(LexItem(symbol, lex_grammar.rule(symbol)));
                }

                state.lex_state_id = add_lex_state(item_set);
            }

            LexStateId add_lex_state(const LexItemSet &item_set) {
                auto state_id = lex_state_id_for_item_set(item_set);
                if (state_id == NOT_FOUND) {
                    state_id = lex_table.add_state();
                    lex_state_ids[item_set] = state_id;
                    add_advance_actions(item_set, state_id);
                    add_accept_token_actions(item_set, state_id);
                }
                return state_id;
            }

            ParseStateId add_parse_state(const ParseItemSet &item_set) {
                auto state_id = parse_state_id_for_item_set(item_set);
                if (state_id == NOT_FOUND) {
                    state_id = parse_table.add_state();
                    parse_state_ids[item_set] = state_id;

                    add_shift_actions(item_set, state_id);
                    add_reduce_actions(item_set, state_id);
                    assign_lex_state(state_id);
                }
                return state_id;
            }

            void add_error_lex_state() {
                LexItemSet error_item_set;
                for (auto &pair : lex_grammar.rules)
                    error_item_set.insert(LexItem(Symbol(pair.first), pair.second));
                for (auto &pair : lex_grammar.aux_rules)
                    error_item_set.insert(LexItem(Symbol(pair.first, rules::SymbolTypeAuxiliary), pair.second));
                add_advance_actions(error_item_set, LexTable::ERROR_STATE_ID);
                add_accept_token_actions(error_item_set, LexTable::ERROR_STATE_ID);
            }

//            void dump_item_sets() {
//                std::vector<const ParseItemSet *> item_sets(parse_state_ids.size());
//                for (auto &pair : parse_state_ids)
//                    item_sets[pair.second] = &pair.first;
//
//                for (int i = 0; i < item_sets.size(); i++) {
//                    std:cout << "\n\n" << i;
//                    for (auto &item : *item_sets[i]) {
//                        cout << "\n" << item.lhs;
//                        cout << "\n  " << item.rule;
//                        cout << "\n  " << item.lookahead_sym.name;
//                    }
//                }
//            }

        public:

            TableBuilder(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar) :
                grammar(grammar),
                lex_grammar(lex_grammar) {}

            pair<ParseTable, LexTable> build() {
                ParseItem item(rules::START, make_shared<Symbol>(grammar.start_rule_name), {}, rules::END_OF_INPUT);
                ParseItemSet item_set = item_set_closure(ParseItemSet({ item }), grammar);
                add_parse_state(item_set);
                add_error_lex_state();
                return pair<ParseTable, LexTable>(parse_table, lex_table);
            }
        };

        pair<ParseTable, LexTable> build_tables(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar) {
            return TableBuilder(grammar, lex_grammar).build();
        }
    }
}
