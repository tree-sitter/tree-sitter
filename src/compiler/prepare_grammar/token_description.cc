#include "compiler/prepare_grammar/token_description.h"
#include "tree_sitter/compiler.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;

class TokenDescription : public rules::RuleFn<string> {
  string apply_to(const rules::Pattern *rule) {
    return "PAT_" + util::escape_string(rule->value);
  }

  string apply_to(const rules::String *rule) {
    return "STR_" + util::escape_string(rule->value);
  }

  string apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  string apply_to(const rules::Seq *rule) {
    return "(seq " + apply(rule->left) + " " + apply(rule->right) + ")";
  }

  string apply_to(const rules::Choice *rule) {
    string result = "(choice";
    for (auto &element : rule->elements)
      result += " " + apply(element);
    return result + ")";
  }
};

std::string token_description(const rule_ptr &rule) {
  return TokenDescription().apply(rule);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
