#include "table_builder.h"
#include "item_set.h"
#include "rules.h"
#include "grammar.h"

using std::pair;
using std::vector;

namespace tree_sitter {
    namespace lr {
        static int NOT_FOUND = -1;

        class TableBuilder {
            const Grammar grammar;
            const Grammar lex_grammar;
            std::unordered_map<const ItemSet, size_t> parse_state_indices;
            std::unordered_map<const ItemSet, size_t> lex_state_indices;
            ParseTable parse_table;
            LexTable lex_table;
            
            long parse_state_index_for_item_set(const ItemSet &item_set) const {
                auto entry = parse_state_indices.find(item_set);
                return (entry == parse_state_indices.end()) ? NOT_FOUND : entry->second;
            }

            long lex_state_index_for_item_set(const ItemSet &item_set) const {
                auto entry = lex_state_indices.find(item_set);
                return (entry == lex_state_indices.end()) ? NOT_FOUND : entry->second;
            }
            
            void add_shift_actions(const ItemSet &item_set, size_t state_index) {
                auto x = item_set.sym_transitions(grammar);
                for (auto transition : x) {
                    
                    rules::Symbol symbol = *transition.first;
                    ItemSet item_set = *transition.second;
                    size_t new_state_index = add_parse_state(item_set);
                    parse_table.add_action(state_index, symbol.name, ParseAction::Shift(new_state_index));
                }
            }
            
            void add_advance_actions(const ItemSet &item_set, size_t state_index) {
                for (auto transition : item_set.char_transitions(grammar)) {
                    rules::Character rule = *transition.first;
                    ItemSet item_set = *transition.second;
                    size_t new_state_index = add_lex_state(item_set);
                    lex_table.add_action(state_index, rule.value, LexAction::Advance(new_state_index));
                }
            }
            
            void add_accept_token_actions(const ItemSet &item_set, size_t state_index) {
                for (Item item : item_set) {
                    if (item.is_done()) {
                        lex_table.add_default_action(state_index, LexAction::Accept(item.rule_name));
                    }
                }
            }

            void add_reduce_actions(const ItemSet &item_set, size_t state_index) {
                for (Item item : item_set) {
                    if (item.is_done()) {
                        if (item.rule_name == ParseTable::START) {
                            parse_table.add_action(state_index, ParseTable::END_OF_INPUT, ParseAction::Accept());
                        } else {
                            parse_table.add_default_action(state_index, ParseAction::Reduce(item.rule_name, item.consumed_sym_count));
                        }
                    }
                }
            }
            
            size_t add_lex_state(const ItemSet &item_set) {
                auto state_index = lex_state_index_for_item_set(item_set);
                if (state_index == NOT_FOUND) {
                    state_index = lex_table.add_state();
                    lex_state_indices[item_set] = state_index;
                    add_advance_actions(item_set, state_index);
                    add_accept_token_actions(item_set, state_index);
                }
                return state_index;
            }
            
            ItemSet lex_item_set_for_parse_item_set(const ItemSet &parse_item_set) {
                vector<Item> items;
                for (rules::Symbol symbol : parse_item_set.next_terminal_symbols(grammar))
                    items.push_back(Item::at_beginning_of_token(symbol.name, lex_grammar));
                return ItemSet(items);
            }
            
            size_t add_parse_state(const ItemSet &item_set) {
                auto state_index = parse_state_index_for_item_set(item_set);
                if (state_index == NOT_FOUND) {
                    state_index = parse_table.add_state();
                    parse_state_indices[item_set] = state_index;

                    ItemSet lex_item_set = lex_item_set_for_parse_item_set(item_set);
                    parse_table.states[state_index].lex_state_index = add_lex_state(lex_item_set);
                    add_shift_actions(item_set, state_index);
                    add_reduce_actions(item_set, state_index);
                }
                return state_index;
            }
            
        public:
            
            TableBuilder(const Grammar &grammar, const Grammar &lex_grammar) :
                grammar(grammar),
                lex_grammar(lex_grammar) {};

            pair<ParseTable, LexTable> build() {
                auto item = Item(ParseTable::START, rules::sym(grammar.start_rule_name), 0);
                auto item_set = ItemSet(item, grammar);
                add_parse_state(item_set);
                return pair<ParseTable, LexTable>(parse_table, lex_table);
            }
        };
        
        pair<ParseTable, LexTable> build_tables(const Grammar &grammar, const Grammar &lex_grammar) {
            return TableBuilder(grammar, lex_grammar).build();
        }
    }
}