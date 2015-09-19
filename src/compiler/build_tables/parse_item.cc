#include "compiler/build_tables/parse_item.h"
#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::vector;
using std::ostream;

ParseItem::ParseItem(const rules::Symbol &lhs, const rule_ptr rule,
                     const vector<rules::Symbol> &consumed_symbols)
    : Item(lhs, rule), consumed_symbols(consumed_symbols) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (lhs == other.lhs) &&
         (consumed_symbols.size() == other.consumed_symbols.size()) &&
         (rule == other.rule || rule->operator==(*other.rule));
}

bool ParseItem::operator<(const ParseItem &other) const {
  if (lhs < other.lhs)
    return true;
  if (other.lhs < lhs)
    return false;
  if (consumed_symbols.size() < other.consumed_symbols.size())
    return true;
  if (other.consumed_symbols.size() < consumed_symbols.size())
    return false;
  return rule < other.rule;
}

}  // namespace build_tables
}  // namespace tree_sitter
