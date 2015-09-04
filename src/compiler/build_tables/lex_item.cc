#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/get_metadata.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::ostream;

LexItem::LexItem(const rules::Symbol &lhs, const rule_ptr rule)
    : Item(lhs, rule) {}

bool LexItem::operator==(const LexItem &other) const {
  return (other.lhs == lhs) && other.rule->operator==(*rule);
}

bool LexItem::is_token_start() const {
  return get_metadata(rule, rules::START_TOKEN).max > 0;
}

ostream &operator<<(ostream &stream, const LexItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

}  // namespace build_tables
}  // namespace tree_sitter
