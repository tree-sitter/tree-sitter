#include "compiler/build_tables/parse_item.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::vector;
using std::ostream;

ParseItem::ParseItem(const rules::Symbol &lhs, const rules::rule_ptr rule,
                     const vector<rules::Symbol> &consumed_symbols)
    : Item(lhs, rule), consumed_symbols(consumed_symbols) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (lhs == other.lhs) &&
         (consumed_symbols.size() == other.consumed_symbols.size()) &&
         (rule == other.rule || rule->operator==(*other.rule));
}

ostream &operator<<(ostream &stream, const ParseItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

}  // namespace build_tables
}  // namespace tree_sitter
