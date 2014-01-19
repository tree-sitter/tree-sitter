#include "item_set_transitions.h"
#include "item_set_closure.h"
#include "rule_transitions.h"

using std::dynamic_pointer_cast;
using std::make_shared;

namespace tree_sitter {
    namespace build_tables {
        transition_map<rules::Character, LexItemSet> char_transitions(const LexItemSet &item_set, const Grammar &grammar) {
            transition_map<rules::Character, LexItemSet> result;
            for (LexItem item : item_set) {
                for (auto transition : rule_transitions(item.rule)) {
                    auto new_item = LexItem(item.rule_name, transition.second);
                    auto rule = dynamic_pointer_cast<const rules::Character>(transition.first);
                    if (rule.get()) {
                        auto new_item_set = make_shared<LexItemSet>(LexItemSet({ new_item }));
                        result.add(rule, new_item_set);
                    }
                }
            }
            return result;
        }
        
        transition_map<rules::Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const Grammar &grammar) {
            transition_map<rules::Symbol, ParseItemSet> result;
            for (ParseItem item : item_set) {
                for (auto transition : rule_transitions(item.rule)) {
                    auto new_item = ParseItem(item.rule_name, transition.second, item.consumed_sym_count + 1, item.lookahead_sym_name);
                    auto rule = dynamic_pointer_cast<const rules::Symbol>(transition.first);
                    if (rule.get()) {
                        auto new_item_set = make_shared<ParseItemSet>(item_set_closure(ParseItemSet({ new_item }), grammar));
                        result.add(rule, new_item_set);
                    }
                }
            }
            return result;
        }
    }
}