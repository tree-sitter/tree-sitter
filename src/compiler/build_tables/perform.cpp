#include "./perform.h"
#include "item.h"
#include "item_set_closure.h"
#include "first_set.h"
#include "item_set_transitions.h"
#include "rules.h"
#include "grammar.h"

using std::pair;
using std::string;
using std::vector;
using std::unordered_map;

namespace tree_sitter {
    namespace build_tables {
        static int NOT_FOUND = -1;
        static string START = "__START__";
        static string END_OF_INPUT = "__END__";

        class TableBuilder {
            const Grammar grammar;
            const Grammar lex_grammar;
            unordered_map<const ParseItemSet, size_t> parse_state_indices;
            unordered_map<const LexItemSet, size_t> lex_state_indices;
            ParseTable parse_table;
            LexTable lex_table;
            
            long parse_state_index_for_item_set(const ParseItemSet &item_set) const {
                auto entry = parse_state_indices.find(item_set);
                return (entry == parse_state_indices.end()) ? NOT_FOUND : entry->second;
            }

            long lex_state_index_for_item_set(const LexItemSet &item_set) const {
                auto entry = lex_state_indices.find(item_set);
                return (entry == lex_state_indices.end()) ? NOT_FOUND : entry->second;
            }
            
            void add_shift_actions(const ParseItemSet &item_set, size_t state_index) {
                auto x = sym_transitions(item_set, grammar);
                for (auto transition : x) {
                    rules::Symbol symbol = *transition.first;
                    ParseItemSet item_set = *transition.second;
                    size_t new_state_index = add_parse_state(item_set);
                    parse_table.add_action(state_index, symbol.name, ParseAction::Shift(new_state_index));
                }
            }
            
            void add_advance_actions(const LexItemSet &item_set, size_t state_index) {
                for (auto transition : char_transitions(item_set, grammar)) {
                    rules::Character rule = *transition.first;
                    LexItemSet item_set = *transition.second;
                    size_t new_state_index = add_lex_state(item_set);
                    lex_table.add_action(state_index, rule.value, LexAction::Advance(new_state_index));
                }
            }
            
            void add_accept_token_actions(const LexItemSet &item_set, size_t state_index) {
                for (LexItem item : item_set) {
                    if (item.is_done()) {
                        lex_table.add_default_action(state_index, LexAction::Accept(item.rule_name));
                    }
                }
            }

            void add_reduce_actions(const ParseItemSet &item_set, size_t state_index) {
                for (ParseItem item : item_set) {
                    if (item.is_done()) {
                        ParseAction action = (item.rule_name == START) ?
                            ParseAction::Accept() :
                            ParseAction::Reduce(item.rule_name, item.consumed_sym_count);
                        parse_table.add_action(state_index, item.lookahead_sym_name, action);
                    }
                }
            }
            
            void assign_lex_state(size_t state_index) {
                ParseState &state = parse_table.states[state_index];
                LexItemSet item_set;
                for (auto pair : state.actions) {
                    auto symbol = rules::Symbol(pair.first);
                    if (symbol.name == END_OF_INPUT)
                        item_set.insert(LexItem(symbol.name, rules::character('\0')));
                    if (lex_grammar.has_definition(symbol))
                        item_set.insert(LexItem(symbol.name, lex_grammar.rule(symbol.name)));
                }

                state.lex_state_index = add_lex_state(item_set);
            }
            
            size_t add_lex_state(const LexItemSet &item_set) {
                auto state_index = lex_state_index_for_item_set(item_set);
                if (state_index == NOT_FOUND) {
                    state_index = lex_table.add_state();
                    lex_state_indices[item_set] = state_index;
                    add_advance_actions(item_set, state_index);
                    add_accept_token_actions(item_set, state_index);
                }
                return state_index;
            }
            
            size_t add_parse_state(const ParseItemSet &item_set) {
                auto state_index = parse_state_index_for_item_set(item_set);
                if (state_index == NOT_FOUND) {
                    state_index = parse_table.add_state();
                    parse_state_indices[item_set] = state_index;

                    add_shift_actions(item_set, state_index);
                    add_reduce_actions(item_set, state_index);
                    assign_lex_state(state_index);
                }
                return state_index;
            }
            
        public:
            
            TableBuilder(const Grammar &grammar, const Grammar &lex_grammar) :
                grammar(grammar),
                lex_grammar(lex_grammar) {};

            pair<ParseTable, LexTable> build() {
                auto item = ParseItem(START, rules::sym(grammar.start_rule_name), 0, END_OF_INPUT);
                ParseItemSet item_set = item_set_closure(ParseItemSet({ item }), grammar);
                add_parse_state(item_set);
                return pair<ParseTable, LexTable>(parse_table, lex_table);
            }
        };
        
        pair<ParseTable, LexTable> perform(const Grammar &grammar, const Grammar &lex_grammar) {
            return TableBuilder(grammar, lex_grammar).build();
        }
    }
}