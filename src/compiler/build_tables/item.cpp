#include "item.h"
#include "grammar.h"
#include "rule_transitions.h"

using std::string;
using std::ostream;

namespace tree_sitter {
    namespace build_tables {
        const int NO_SYMBOLS = -1;
        
        Item::Item(const string &rule_name, const rules::rule_ptr rule, int consumed_sym_count) :
            rule_name(rule_name),
            rule(rule),
            consumed_sym_count(consumed_sym_count) {};
        
        Item Item::at_beginning_of_rule(const string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), 0);
        }

        Item Item::at_beginning_of_token(const string &rule_name, const Grammar &grammar) {
            return Item(rule_name, grammar.rule(rule_name), NO_SYMBOLS);
        }
        
        int Item::next_sym_count() const {
            return (consumed_sym_count == NO_SYMBOLS) ? NO_SYMBOLS : (consumed_sym_count + 1);
        }

        bool Item::operator==(const Item &other) const {
            bool rule_names_eq = other.rule_name == rule_name;
            bool rules_eq = (*other.rule == *rule);
            bool consumed_sym_counts_eq = (other.consumed_sym_count == consumed_sym_count);
            return rule_names_eq && rules_eq && consumed_sym_counts_eq;
        }
        
        bool Item::is_done() const {
            for (auto pair : rule_transitions(rule))
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

