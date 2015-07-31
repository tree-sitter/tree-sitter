#include "tree_sitter/compiler.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"

namespace tree_sitter {
namespace prepare_grammar {

class IsToken : public rules::RuleFn<bool> {
  bool apply_to(const rules::String *rule) {
    return true;
  }
  bool apply_to(const rules::Pattern *rule) {
    return true;
  }
  bool apply_to(const rules::Metadata *rule) {
    return rule->value_for(rules::IS_TOKEN);
  }
};

bool is_token(const rules::rule_ptr &rule) {
  return IsToken().apply(rule);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
