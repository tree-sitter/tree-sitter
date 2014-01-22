#include "item.h"
#include "grammar.h"
#include "rule_transitions.h"

using std::string;
using std::to_string;
using std::ostream;

namespace tree_sitter {
    namespace build_tables {
        Item::Item(const string &rule_name, const rules::rule_ptr rule) :
            rule_name(rule_name),
            rule(rule) {};
        
        bool Item::is_done() const {
            return rule_can_be_blank(rule);
        }
        
        ostream& operator<<(ostream &stream, const LexItem &item) {
            return stream <<
            string("#<item '") <<
            item.rule_name <<
            string("' ") <<
            *item.rule <<
            string(">");
        }
        
        ostream& operator<<(ostream &stream, const ParseItem &item) {
            return stream <<
            string("#<item '") <<
            item.rule_name <<
            string("' ") <<
            *item.rule <<
            string(" ") <<
            to_string(item.consumed_sym_count) <<
            string(" ") <<
            item.lookahead_sym_name <<
            string(">");
        }
        
        bool LexItem::operator<(const LexItem &other) const {
            if (rule_name < other.rule_name) return true;
            if (rule->to_string() < other.rule->to_string()) return true;
            return false;
        }

        bool ParseItem::operator<(const ParseItem &other) const {
            if (rule_name < other.rule_name) return true;
            if (rule_name > other.rule_name) return false;
            if (rule->to_string() < other.rule->to_string()) return true;
            if (rule->to_string() > other.rule->to_string()) return false;
            if (consumed_sym_count < other.consumed_sym_count) return true;
            if (lookahead_sym_name < other.lookahead_sym_name) return true;
            return false;
        }

        LexItem::LexItem(const std::string &rule_name, const rules::rule_ptr rule) : Item(rule_name, rule) {}
        
        bool LexItem::operator==(const LexItem &other) const {
            bool rule_names_eq = other.rule_name == rule_name;
            bool rules_eq = (*other.rule == *rule);
            return rule_names_eq && rules_eq;
        }
        
        ParseItem::ParseItem(const std::string &rule_name, const rules::rule_ptr rule, int consumed_sym_count, const std::string &lookahead_sym_name) :
            Item(rule_name, rule),
            consumed_sym_count(consumed_sym_count),
            lookahead_sym_name(lookahead_sym_name) {}

        bool ParseItem::operator==(const ParseItem &other) const {
            bool rule_names_eq = other.rule_name == rule_name;
            bool rules_eq = (*other.rule == *rule);
            bool consumed_sym_counts_eq = (other.consumed_sym_count == consumed_sym_count);
            bool lookaheads_eq = other.lookahead_sym_name == lookahead_sym_name;
            return rule_names_eq && rules_eq && consumed_sym_counts_eq && lookaheads_eq;
        }
    }
}

