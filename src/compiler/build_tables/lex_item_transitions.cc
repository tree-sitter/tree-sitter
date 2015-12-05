#include "compiler/build_tables/lex_item_transitions.h"
#include <map>
#include <vector>
#include <functional>
#include <utility>
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
  LexItemSet::TransitionMap *transitions;
  const rules::Symbol &item_lhs;
  vector<int> *precedence_stack;

  LexItemSet transform_item_set(const LexItemSet &item_set,
                                function<rule_ptr(rule_ptr)> callback) {
    LexItemSet new_set;
    for (const LexItem &item : item_set.entries)
      new_set.entries.insert(LexItem(item.lhs, callback(item.rule)));
    return new_set;
  }

  void merge_transition(LexItemSet::TransitionMap *transitions,
                        CharacterSet new_char_set, LexItemSet new_item_set,
                        PrecedenceRange new_precedence_range) {
    vector<pair<CharacterSet, pair<LexItemSet, PrecedenceRange>>> new_entries;

    auto iter = transitions->begin();
    while (iter != transitions->end()) {
      CharacterSet existing_char_set = iter->first;
      LexItemSet &existing_item_set = iter->second.first;
      PrecedenceRange &existing_precedence_range = iter->second.second;

      CharacterSet intersection = existing_char_set.remove_set(new_char_set);
      if (!intersection.is_empty()) {
        new_char_set.remove_set(intersection);
        if (!existing_char_set.is_empty())
          new_entries.push_back(
            { existing_char_set,
              { existing_item_set, existing_precedence_range } });
        existing_item_set.entries.insert(new_item_set.entries.begin(),
                                         new_item_set.entries.end());
        existing_precedence_range.add(new_precedence_range);
        new_entries.push_back(
          { intersection, { existing_item_set, existing_precedence_range } });
        transitions->erase(iter++);
      } else {
        iter++;
      }
    }

    transitions->insert(new_entries.begin(), new_entries.end());

    if (!new_char_set.is_empty())
      transitions->insert(
        { new_char_set, { new_item_set, new_precedence_range } });
  }

  map<rules::MetadataKey, int> activate_precedence(
    map<rules::MetadataKey, int> metadata) {
    if (metadata.find(rules::PRECEDENCE) != metadata.end())
      metadata.insert({ rules::IS_ACTIVE, 1 });
    return metadata;
  }

  void apply_to(const CharacterSet *rule) {
    PrecedenceRange precedence;
    if (!precedence_stack->empty())
      precedence.add(precedence_stack->back());

    merge_transition(transitions, *rule,
                     LexItemSet({ LexItem(item_lhs, rules::Blank::build()) }),
                     precedence);
  }

  void apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements)
      apply(element);
  }

  void apply_to(const rules::Seq *rule) {
    LexItemSet::TransitionMap left_transitions;
    LexItemTransitions(&left_transitions, this).apply(rule->left);
    for (const auto &pair : left_transitions) {
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second.first, [&rule](rule_ptr item_rule) {
          return rules::Seq::build({ item_rule, rule->right });
        }), pair.second.second);
    }

    if (rule_can_be_blank(rule->left))
      apply(rule->right);
  }

  void apply_to(const rules::Repeat *rule) {
    LexItemSet::TransitionMap content_transitions;
    LexItemTransitions(&content_transitions, this).apply(rule->content);
    for (const auto &pair : content_transitions) {
      merge_transition(transitions, pair.first, pair.second.first,
                       pair.second.second);
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second.first, [&rule](rule_ptr item_rule) {
          return rules::Seq::build({ item_rule, rule->copy() });
        }), pair.second.second);
    }
  }

  void apply_to(const rules::Metadata *rule) {
    LexItemSet::TransitionMap content_transitions;
    auto precedence = rule->value_for(rules::PRECEDENCE);
    bool has_active_precedence =
      precedence.second && rule->value_for(rules::IS_ACTIVE).second;
    if (has_active_precedence)
      precedence_stack->push_back(precedence.first);

    LexItemTransitions(&content_transitions, this).apply(rule->rule);
    for (const auto &pair : content_transitions)
      merge_transition(
        transitions, pair.first,
        transform_item_set(pair.second.first, [this, &rule](rule_ptr item_rule) {
          return rules::Metadata::build(item_rule,
                                        activate_precedence(rule->value));
        }), pair.second.second);

    if (has_active_precedence)
      precedence_stack->pop_back();
  }

 public:
  LexItemTransitions(LexItemSet::TransitionMap *transitions,
                     const rules::Symbol &item_lhs,
                     vector<int> *precedence_stack)
      : transitions(transitions),
        item_lhs(item_lhs),
        precedence_stack(precedence_stack) {}

  LexItemTransitions(LexItemSet::TransitionMap *transitions,
                     LexItemTransitions *other)
      : transitions(transitions),
        item_lhs(other->item_lhs),
        precedence_stack(other->precedence_stack) {}
};

void lex_item_transitions(LexItemSet::TransitionMap *transitions,
                          const LexItem &item) {
  vector<int> precedence_stack;
  LexItemTransitions(transitions, item.lhs, &precedence_stack).apply(item.rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
