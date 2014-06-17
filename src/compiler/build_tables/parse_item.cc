#include "compiler/build_tables/parse_item.h"
#include <set>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    using std::pair;
    using std::set;
    using std::string;
    using std::to_string;
    using std::ostream;

    namespace build_tables {
        ParseItem::ParseItem(const rules::Symbol &lhs,
                             const rules::rule_ptr rule,
                             size_t consumed_symbol_count) :
            Item(lhs, rule),
            consumed_symbol_count(consumed_symbol_count) {}

        bool ParseItem::operator==(const ParseItem &other) const {
            return
                (lhs == other.lhs) &&
                (consumed_symbol_count == other.consumed_symbol_count) &&
                (rule == other.rule || rule->operator==(*other.rule));
        }

        ostream& operator<<(ostream &stream, const ParseItem &item) {
            return stream << string("#<item ") << item.lhs << string(" ") << *item.rule << string(">");
        }
    }
}

