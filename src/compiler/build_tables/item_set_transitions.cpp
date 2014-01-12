#include "item_set_transitions.h"
#include "close_item_set.h"
#include "rule_transitions.h"

using std::dynamic_pointer_cast;
using std::make_shared;

namespace tree_sitter {
    namespace build_tables {
        transition_map<rules::Rule, Item> item_transitions(const Item &item) {
            return rule_transitions(item.rule).map<Item>([&](rules::rule_ptr to_rule) {
                return make_shared<Item>(item.rule_name, to_rule, item.next_sym_count());
            });
        };
        
        template<typename RuleClass>
        transition_map<RuleClass, ItemSet> transitions(const ItemSet &item_set, const Grammar &grammar) {
            transition_map<RuleClass, ItemSet> result;
            for (Item item : item_set) {
                for (auto transition : item_transitions(item)) {
                    auto rule = dynamic_pointer_cast<const RuleClass>(transition.first);
                    auto new_item_set = make_shared<ItemSet>(close_item_set(ItemSet({ *transition.second }), grammar));
                    if (rule.get()) result.add(rule, new_item_set);
                }
            }
            return result;
        }
        
        transition_map<rules::Character, ItemSet> char_transitions(const ItemSet &item_set, const Grammar &grammar) {
            return transitions<rules::Character>(item_set, grammar);
        }
        
        transition_map<rules::Symbol, ItemSet> sym_transitions(const ItemSet &item_set, const Grammar &grammar) {
            return transitions<rules::Symbol>(item_set, grammar);
        }
    }
}