#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/repeat.h"

namespace tree_sitter {
namespace build_tables {

class CanBeBlank : public rules::RuleFn<bool> {
 protected:
  bool apply_to(const rules::Blank *) {
    return true;
  }

  bool apply_to(const rules::Repeat *rule) {
    return apply(rule->content);
  }

  bool apply_to(const rules::Choice *rule) {
    for (const auto &element : rule->elements)
      if (apply(element))
        return true;
    return false;
  }

  bool apply_to(const rules::Seq *rule) {
    return apply(rule->left) && apply(rule->right);
  }

  bool apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }
};

bool rule_can_be_blank(const rule_ptr &rule) {
  return CanBeBlank().apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
