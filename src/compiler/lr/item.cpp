#include "item.h"
#include "grammar.h"
#include "transitions.h"

#include <iostream>

using namespace std;

namespace tree_sitter {
    namespace lr {
        Item::Item(const std::string &rule_name, const rules::rule_ptr rule, int consumed_sym_count) :
            rule_name(rule_name),
            rule(rule),
            consumed_sym_count(consumed_sym_count) {};
        
        Item Item::at_beginning_of_rule(const std::string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), 0);
        }

        Item Item::at_beginning_of_token(const std::string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), -1);
        }

        transition_map<rules::Rule, Item> Item::transitions() const {
            return lr::transitions(rule).map<Item>([&](rules::rule_ptr to_rule) -> item_ptr {
                int next_sym_count = (consumed_sym_count == -1) ? -1 : (consumed_sym_count + 1);
                return std::make_shared<Item>(rule_name, to_rule, next_sym_count);
            });
        };
        
        vector<rules::Symbol> Item::next_symbols() const {
            vector<rules::Symbol> result;
            for (auto pair : lr::transitions(rule)) {
                auto sym = dynamic_pointer_cast<const rules::Symbol>(pair.first);
                if (sym) result.push_back(*sym);
            }
            return result;
        }
    
        bool Item::operator==(const Item &other) const {
            bool rule_names_eq = other.rule_name == rule_name;
            bool rules_eq = (*other.rule == *rule);
            bool consumed_sym_counts_eq = (other.consumed_sym_count == consumed_sym_count);
            return rule_names_eq && rules_eq && consumed_sym_counts_eq;
        }
        
        bool Item::is_done() const {
            for (auto pair : transitions())
                if (*pair.first == rules::Blank())
                    return true;
            return false;
        }
        
        std::ostream& operator<<(ostream &stream, const Item &item) {
            return stream <<
                string("#<item '") <<
                item.rule_name <<
                string("' ") <<
                *item.rule <<
                string(">");
        }
    }
}

