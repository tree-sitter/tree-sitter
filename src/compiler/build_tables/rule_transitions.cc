#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::make_shared;
using rules::CharacterSet;
using rules::Choice;
using rules::Symbol;

class RuleTransitions : public rules::RuleFn<map<CharacterSet, rule_ptr>> {
 private:
  void merge_transitions(map<CharacterSet, rule_ptr> *left,
                         const map<CharacterSet, rule_ptr> &right) {
    for (auto &pair : right)
      merge_transition<rule_ptr>(left, pair,
                                 [](rule_ptr *left, const rule_ptr *right) {
                                   *left = Choice::build({ *left, *right });
                                 });
  }

  map<CharacterSet, rule_ptr> apply_to(const CharacterSet *rule) {
    return map<CharacterSet, rule_ptr>(
      { { *rule, make_shared<rules::Blank>() } });
  }

  map<CharacterSet, rule_ptr> apply_to(const rules::Choice *rule) {
    map<CharacterSet, rule_ptr> result;
    for (const auto &el : rule->elements)
      merge_transitions(&result, this->apply(el));
    return result;
  }

  map<CharacterSet, rule_ptr> apply_to(const rules::Seq *rule) {
    auto result = this->apply(rule->left);
    for (auto &pair : result)
      pair.second = rules::Seq::build({ pair.second, rule->right });
    if (rule_can_be_blank(rule->left))
      merge_transitions(&result, this->apply(rule->right));
    return result;
  }

  map<CharacterSet, rule_ptr> apply_to(const rules::Repeat *rule) {
    auto result = this->apply(rule->content);
    for (auto &pair : result)
      pair.second = rules::Seq::build({ pair.second, rule->copy() });
    return result;
  }

  map<CharacterSet, rule_ptr> apply_to(const rules::Metadata *rule) {
    auto result = this->apply(rule->rule);
    for (auto &pair : result)
      pair.second = make_shared<rules::Metadata>(pair.second, rule->value);
    return result;
  }
};

map<CharacterSet, rule_ptr> rule_transitions(const rule_ptr &rule) {
  return RuleTransitions().apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
