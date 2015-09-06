#include "compiler/prepare_grammar/token_description.h"
#include "tree_sitter/compiler.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/string.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/metadata.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;

class TokenDescription : public rules::RuleFn<string> {
  string apply_to(const rules::Pattern *rule) {
    is_trivial = false;
    return rule->value;
  }

  string apply_to(const rules::String *rule) {
    return rule->value;
  }

  string apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  string apply_to(const rules::Seq *rule) {
    is_trivial = false;
    return apply(rule->left) + apply(rule->right);
  }

  string apply_to(const rules::Repeat *rule) {
    is_trivial = false;
    return apply(rule->content) + "*";
  }

  string apply_to(const rules::Choice *rule) {
    is_trivial = false;
    string result = "(";
    bool started = false;
    for (auto &element : rule->elements) {
      if (started)
        result += "|";
      result += apply(element);
      started = true;
    }
    return result + ")";
  }

 public:
  bool is_trivial;

  TokenDescription() : is_trivial(true) {}
};

string token_description(const rule_ptr &rule) {
  TokenDescription description;
  string result = description.apply(rule);
  if (description.is_trivial)
    return result;
  else
    return "/" + result + "/";
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
