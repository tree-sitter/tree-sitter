#include "item.h"

namespace tree_sitter {
    namespace lr {
        Item::Item(const std::string &rule_name, rules::rule_ptr rule, int consumed_sym_count) :
            rule_name(rule_name),
            rule(rule),
            consumed_sym_count(consumed_sym_count) {};
        
        TransitionMap<Item> Item::transitions() const {
            return rule->transitions().map<Item>([&](rules::rule_ptr to_rule) {
                return item_ptr(new Item(rule_name, to_rule, consumed_sym_count + 1));
            });
        };
    }
}