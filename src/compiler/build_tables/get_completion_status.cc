#include "compiler/build_tables/get_completion_status.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
namespace build_tables {

class GetCompletionStatus : public rules::RuleFn<CompletionStatus> {
 protected:
  CompletionStatus apply_to(const rules::Choice *rule) {
    for (const auto &element : rule->elements) {
      CompletionStatus status = apply(element);
      if (status.is_done)
        return status;
    }
    return { false, 0, AssociativityNone };
  }

  CompletionStatus apply_to(const rules::Metadata *rule) {
    CompletionStatus result = apply(rule->rule);
    if (result.is_done && !result.associativity) {
      result.precedence = rule->value_for(rules::PRECEDENCE);
      result.associativity =
        (Associativity)(rule->value_for(rules::ASSOCIATIVITY));
    }
    return result;
  }

  CompletionStatus apply_to(const rules::Repeat *rule) {
    return { true, 0, AssociativityNone };
  }

  CompletionStatus apply_to(const rules::Blank *rule) {
    return { true, 0, AssociativityNone };
  }

  CompletionStatus apply_to(const rules::Seq *rule) {
    CompletionStatus left_status = apply(rule->left);
    if (left_status.is_done)
      return apply(rule->right);
    else
      return { false, 0, AssociativityNone };
  }
};

CompletionStatus get_completion_status(const rule_ptr &rule) {
  return GetCompletionStatus().apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
