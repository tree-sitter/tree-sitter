#include "item.h"
#include "grammar.h"

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
        
        TransitionMap<Item> Item::transitions() const {
            return rule->transitions().map<Item>([&](rules::rule_ptr to_rule) {
                return std::make_shared<Item>(rule_name, to_rule, consumed_sym_count + 1);
            });
        };
        
        vector<rules::sym_ptr> Item::next_symbols() const {
            vector<rules::sym_ptr> result;
            for (auto pair : rule->transitions()) {
                shared_ptr<const rules::Symbol> sym = dynamic_pointer_cast<const rules::Symbol>(pair.first);
                if (sym) result.push_back(sym);
            }
            return result;
        }
    
        bool Item::operator==(const Item &other) const {
            bool rule_names_eq = other.rule_name == rule_name;
            bool rules_eq = (*other.rule == *rule);
            return rule_names_eq && rules_eq;
        }
        
        std::ostream& operator<<(ostream &stream, const Item &item) {
            stream <<
                string("(item '") <<
                item.rule_name <<
                string("' ") <<
                *item.rule <<
                string(")");
            return stream;
        }
    }
}


