#include "item.h"
#include "grammar.h"
#include "rule_transitions.h"

using std::string;
using std::vector;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::ostream;

namespace tree_sitter {
    namespace build_tables {
        Item::Item(const string &rule_name, const rules::rule_ptr rule, int consumed_sym_count) :
            rule_name(rule_name),
            rule(rule),
            consumed_sym_count(consumed_sym_count) {};
        
        Item Item::at_beginning_of_rule(const string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), 0);
        }

        Item Item::at_beginning_of_token(const string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), -1);
        }

        transition_map<rules::Rule, Item> Item::transitions() const {
            return rule_transitions(rule).map<Item>([&](rules::rule_ptr to_rule) -> item_ptr {
                int next_sym_count = (consumed_sym_count == -1) ? -1 : (consumed_sym_count + 1);
                return make_shared<Item>(rule_name, to_rule, next_sym_count);
            });
        };
        
        vector<rules::Symbol> Item::next_symbols() const {
            vector<rules::Symbol> result;
            for (auto pair : rule_transitions(rule)) {
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
        
        ostream& operator<<(ostream &stream, const Item &item) {
            return stream <<
                string("#<item '") <<
                item.rule_name <<
                string("' ") <<
                *item.rule <<
                string(">");
        }
    }
}

