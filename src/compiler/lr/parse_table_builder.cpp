#include "parse_table_builder.h"
#include <unordered_map>
#include "item_set.h"
#include "rules.h"
#include "item_set.h"
#include "grammar.h"

using namespace std;

namespace tree_sitter {
    namespace lr {
        static int NOT_FOUND = -1;

        class ParseTableBuilder {
            const Grammar grammar;
            std::unordered_map<const ItemSet, size_t> state_indices;
            ParseTable table;
            
            long state_index_for_item_set(const ItemSet &item_set) const {
                auto entry = state_indices.find(item_set);
                return (entry == state_indices.end()) ? NOT_FOUND : entry->second;
            }
            
            void add_shift_actions(const ItemSet &item_set, size_t state_index) {
                for (auto transition : item_set.sym_transitions(grammar)) {
                    rules::sym_ptr symbol = static_pointer_cast<const rules::Symbol>(transition.first);
                    size_t new_state_index = add_item_set(*transition.second);
                    table.add_action(state_index, symbol->name, ParseAction::Shift(new_state_index));
                }
            }
            
            void add_reduce_actions(const ItemSet &item_set, size_t state_index) {
                for (Item item : item_set) {
                    if (item.is_done()) {
                        if (item.rule_name == ParseTable::START) {
                            table.add_action(state_index, ParseTable::END_OF_INPUT, ParseAction::Accept());
                        } else {
                            for (string rule_name : table.symbol_names)
                                table.add_action(state_index, rule_name, ParseAction::Reduce(item.rule_name, item.consumed_sym_count));
                        }
                    }
                }
            }
            
            size_t add_item_set(const ItemSet &item_set) {
                auto state_index = state_index_for_item_set(item_set);
                if (state_index == NOT_FOUND) {
                    state_index = table.add_state();
                    state_indices[item_set] = state_index;
                    
                    add_shift_actions(item_set, state_index);
                    add_reduce_actions(item_set, state_index);
                }
                return state_index;
            }

        public:
            
            ParseTableBuilder(const Grammar &grammar) :
                grammar(grammar),
                table(ParseTable(grammar.rule_names())),
                state_indices(unordered_map<const ItemSet, size_t>())
                {};

            ParseTable build() {
                auto item = Item(ParseTable::START, rules::sym(grammar.start_rule_name), 0);
                auto item_set = ItemSet(item, grammar);
                add_item_set(item_set);
                return table;
            }
        };
        
        ParseTable build_tables(const tree_sitter::Grammar &grammar) {
            return ParseTableBuilder(grammar).build();
        }
    }
}