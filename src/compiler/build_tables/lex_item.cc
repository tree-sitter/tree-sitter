#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::ostream;

LexItem::LexItem(const rules::Symbol &lhs, const rules::rule_ptr rule)
    : Item(lhs, rule) {}

bool LexItem::operator==(const LexItem &other) const {
  return (other.lhs == lhs) && other.rule->operator==(*rule);
}

bool LexItem::is_token_start() const {
  class IsTokenStart : public rules::RuleFn<bool> {
    bool apply_to(const rules::Seq *rule) {
      if (apply(rule->left))
        return true;
      else if (rule_can_be_blank(rule->left))
        return apply(rule->right);
      else
        return false;
    }

    bool apply_to(const rules::Metadata *rule) {
      return rule->value_for(rules::START_TOKEN);
    }
  };

  return IsTokenStart().apply(rule);
}

ostream &operator<<(ostream &stream, const LexItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

}  // namespace build_tables
}  // namespace tree_sitter
