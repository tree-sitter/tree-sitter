#include "compiler/build_tables/parse_item.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::ostream;

ParseItem::ParseItem(const rules::Symbol &lhs, const rules::rule_ptr rule,
                     size_t consumed_symbol_count)
    : Item(lhs, rule), consumed_symbol_count(consumed_symbol_count) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (lhs == other.lhs) &&
         (consumed_symbol_count == other.consumed_symbol_count) &&
         (rule == other.rule || rule->operator==(*other.rule));
}

ostream &operator<<(ostream &stream, const ParseItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

}  // namespace build_tables
}  // namespace tree_sitter
