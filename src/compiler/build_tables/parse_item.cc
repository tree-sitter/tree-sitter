#include "compiler/build_tables/parse_item.h"
#include "compiler/syntax_grammar.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::to_string;
using std::ostream;

ParseItem::ParseItem(const rules::Symbol &lhs, size_t production_index,
                    int rule_id, size_t consumed_symbol_count)
    : lhs(lhs), production_index(production_index),
      rule_id(rule_id),
      consumed_symbol_count(consumed_symbol_count) {}

bool ParseItem::operator==(const ParseItem &other) const {
  return (lhs == other.lhs) &&
    (rule_id == other.rule_id) &&
    (consumed_symbol_count == other.consumed_symbol_count);
}

ostream &operator<<(ostream &stream, const ParseItem &item) {
  return stream << string("(item lhs:") << item.lhs
    << string(" index:") << to_string(item.production_index)
    << string(" remaining_rule:") << to_string(item.rule_id)
    << string(" consumed:") << to_string(item.consumed_symbol_count)
    << string(")");
}

}  // namespace build_tables
}  // namespace tree_sitter
