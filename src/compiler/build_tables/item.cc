#include "compiler/build_tables/item.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    using std::string;
    using std::to_string;
    using std::ostream;
    using std::vector;
    using rules::Symbol;
    using rules::rule_ptr;

    namespace build_tables {
        Item::Item(const Symbol &lhs, const rule_ptr rule) :
            lhs(lhs),
            rule(rule) {};

        bool Item::is_done() const {
            return rule_can_be_blank(rule);
        }

        ostream& operator<<(ostream &stream, const LexItem &item) {
            return stream <<
            string("#<item ") <<
            item.lhs <<
            string(" ") <<
            *item.rule <<
            string(">");
        }

        ostream& operator<<(ostream &stream, const ParseItem &item) {
            return stream <<
            string("#<item ") <<
            item.lhs <<
            string(" ") <<
            *item.rule <<
            string(" ") <<
            to_string(item.consumed_symbols.size()) <<
            string(" ") <<
            item.lookahead_sym <<
            string(">");
        }

        bool LexItem::operator<(const LexItem &other) const {
            if (lhs < other.lhs) return true;
            if (other.lhs < lhs) return false;
            if (rule->to_string() < other.rule->to_string()) return true;
            return false;
        }

        bool ParseItem::operator<(const ParseItem &other) const {
            if (lhs < other.lhs) return true;
            if (other.lhs < lhs) return false;
            if (rule->to_string() < other.rule->to_string()) return true;
            if (rule->to_string() > other.rule->to_string()) return false;
            if (consumed_symbols < other.consumed_symbols) return true;
            if (consumed_symbols > other.consumed_symbols) return false;
            if (lookahead_sym < other.lookahead_sym) return true;
            return false;
        }

        LexItem::LexItem(const Symbol &lhs, const rule_ptr rule) : Item(lhs, rule) {}

        bool LexItem::operator==(const LexItem &other) const {
            bool lhs_eq = other.lhs == lhs;
            bool rules_eq = (*other.rule == *rule);
            return lhs_eq && rules_eq;
        }

        ParseItem::ParseItem(const Symbol &lhs, const rule_ptr rule, const vector<bool> &consumed_symbols, const Symbol &lookahead_sym) :
            Item(lhs, rule),
            consumed_symbols(consumed_symbols),
            lookahead_sym(lookahead_sym) {}

        bool ParseItem::operator==(const ParseItem &other) const {
            bool lhs_eq = other.lhs == lhs;
            bool rules_eq = (*other.rule == *rule);
            bool consumed_sym_counts_eq = (other.consumed_symbols == consumed_symbols);
            bool lookaheads_eq = other.lookahead_sym == lookahead_sym;
            return lhs_eq && rules_eq && consumed_sym_counts_eq && lookaheads_eq;
        }
    }
}

