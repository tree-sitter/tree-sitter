#include "compiler/build_tables/lex_item_transitions.h"
#include <map>
#include <vector>
#include <functional>
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {
namespace build_tables {

using std::function;
using std::make_shared;
using std::map;
using std::pair;
using std::vector;
using rules::CharacterSet;

class LexItemTransitions : public rules::RuleFn<void> {
  map<CharacterSet, LexItemSet> *transitions;
  const rules::Symbol &item_lhs;

  LexItemSet transform_item_set(const LexItemSet &item_set,
                                function<rule_ptr(rule_ptr)> transform) {
    LexItemSet new_set;
    for (const LexItem &item : item_set.entries)
      new_set.entries.insert(LexItem(item.lhs, transform(item.rule)));
    return new_set;
  }

  void merge_transition(map<CharacterSet, LexItemSet> *transitions,
                        CharacterSet new_char_set, LexItemSet new_item_set) {
    vector<pair<CharacterSet, LexItemSet>> new_entries;

    auto iter = transitions->begin();
    while (iter != transitions->end()) {
      CharacterSet existing_char_set = iter->first;
      LexItemSet &existing_item_set = iter->second;

      CharacterSet intersection = existing_char_set.remove_set(new_char_set);
      if (!intersection.is_empty()) {
        new_char_set.remove_set(intersection);
        if (!existing_char_set.is_empty())
          new_entries.push_back({ existing_char_set, existing_item_set });
        existing_item_set.entries.insert(new_item_set.entries.begin(),
                                         new_item_set.entries.end());
        new_entries.push_back({ intersection, existing_item_set });
        transitions->erase(iter++);
      } else {
        iter++;
      }
    }

    transitions->insert(new_entries.begin(), new_entries.end());

    if (!new_char_set.is_empty())
      transitions->insert({ new_char_set, new_item_set });
  }

  void apply_to(const CharacterSet *rule) {
    merge_transition(transitions, *rule,
                     LexItemSet({
                       LexItem(item_lhs, rules::Blank::build()),
                     }));
  }

  void apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements)
      apply(element);
  }

  void apply_to(const rules::Seq *rule) {
    map<CharacterSet, LexItemSet> left_transitions;
    LexItemTransitions(&left_transitions, item_lhs).apply(rule->left);
    for (const auto &pair : left_transitions)
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second, [&rule](rule_ptr item_rule) {
          return rules::Seq::build({ item_rule, rule->right });
        }));

    if (rule_can_be_blank(rule->left))
      apply(rule->right);
  }

  void apply_to(const rules::Repeat *rule) {
    map<CharacterSet, LexItemSet> content_transitions;
    LexItemTransitions(&content_transitions, item_lhs).apply(rule->content);
    for (const auto &pair : content_transitions) {
      merge_transition(transitions, pair.first, pair.second);
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second, [&rule](rule_ptr item_rule) {
          return rules::Seq::build({ item_rule, rule->copy() });
        }));
    }
  }

  void apply_to(const rules::Metadata *rule) {
    map<CharacterSet, LexItemSet> content_transitions;
    LexItemTransitions(&content_transitions, item_lhs).apply(rule->rule);
    for (const auto &pair : content_transitions)
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second, [&rule](rule_ptr item_rule) {
          return rules::Metadata::build(item_rule, rule->value);
        }));
  }

 public:
  LexItemTransitions(map<CharacterSet, LexItemSet> *transitions,
                     const rules::Symbol &item_lhs)
      : transitions(transitions), item_lhs(item_lhs) {}
};

void lex_item_transitions(map<CharacterSet, LexItemSet> *transitions,
                          const LexItem &item) {
  LexItemTransitions(transitions, item.lhs).apply(item.rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
