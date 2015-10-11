#include "compiler/prepare_grammar/extract_choices.h"
#include <vector>
#include <memory>
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/repeat.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::make_shared;
using std::vector;

class ExtractChoices : public rules::RuleFn<vector<rule_ptr>> {
  vector<rule_ptr> default_apply(const Rule *rule) {
    return vector<rule_ptr>({ rule->copy() });
  }

  vector<rule_ptr> apply_to(const rules::Seq *rule) {
    vector<rule_ptr> result;
    for (auto left_entry : apply(rule->left))
      for (auto right_entry : apply(rule->right))
        result.push_back(rules::Seq::build({ left_entry, right_entry }));
    return result;
  }

  vector<rule_ptr> apply_to(const rules::Metadata *rule) {
    vector<rule_ptr> result;
    for (auto entry : apply(rule->rule))
      result.push_back(make_shared<rules::Metadata>(entry, rule->value));
    return result;
  }

  vector<rule_ptr> apply_to(const rules::Choice *rule) {
    vector<rule_ptr> result;
    for (auto element : rule->elements)
      for (auto entry : apply(element))
        result.push_back(entry);
    return result;
  }

  vector<rule_ptr> apply_to(const rules::Repeat *rule) {
    return vector<rule_ptr>({
      rules::Repeat::build(rules::Choice::build(apply(rule->content))),
    });
  }
};

std::vector<rule_ptr> extract_choices(const rule_ptr &rule) {
  return ExtractChoices().apply(rule);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
