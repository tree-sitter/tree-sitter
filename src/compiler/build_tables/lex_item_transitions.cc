#include "compiler/build_tables/lex_item_transitions.h"
#include <map>
#include <vector>
#include <functional>
#include <utility>
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rule.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {
namespace build_tables {

using std::function;
using std::map;
using std::move;
using std::pair;
using std::vector;
using rules::CharacterSet;
using rules::Rule;
using Transition = LexItemSet::Transition;
using TransitionMap = LexItemSet::TransitionMap;

class TransitionBuilder {
  TransitionMap *transitions;
  const rules::Symbol &item_lhs;
  vector<int> *precedence_stack;
  bool in_main_token;

  inline Transition transform_transition(const Transition &transition,
                                         const function<Rule(const Rule &)> &callback) {
    LexItemSet destination;
    for (const LexItem &item : transition.destination.entries) {
      destination.entries.insert(LexItem(item.lhs, callback(item.rule)));
    }
    return Transition{destination, transition.precedence, transition.in_main_token};
  }

  void add_transition(TransitionMap *transitions, CharacterSet new_characters,
                      Transition new_transition) {
    vector<pair<CharacterSet, Transition>> new_entries;

    auto iter = transitions->begin();
    while (iter != transitions->end()) {
      CharacterSet existing_characters = iter->first;
      Transition &existing_transition = iter->second;

      CharacterSet intersecting_characters =
        existing_characters.remove_set(new_characters);
      if (intersecting_characters.is_empty()) {
        iter++;
        continue;
      }

      new_characters.remove_set(intersecting_characters);

      if (!existing_characters.is_empty())
        new_entries.push_back({
          existing_characters, existing_transition,
        });

      existing_transition.destination.entries.insert(
        new_transition.destination.entries.begin(),
        new_transition.destination.entries.end());
      existing_transition.precedence.add(new_transition.precedence);
      existing_transition.in_main_token |= new_transition.in_main_token;

      new_entries.push_back({
        intersecting_characters, existing_transition,
      });

      transitions->erase(iter++);
    }

    transitions->insert(new_entries.begin(), new_entries.end());

    if (!new_characters.is_empty())
      transitions->insert({ new_characters, new_transition });
  }

 public:
  void apply(const Rule &rule) {
    rule.match(
      [](const rules::Blank &) {},

      [this](const rules::CharacterSet &character_set) {
        PrecedenceRange precedence;
        if (!precedence_stack->empty()) {
          precedence.add(precedence_stack->back());
        }

        add_transition(
          transitions,
          character_set,
          Transition{
            LexItemSet({ LexItem(item_lhs, rules::Blank{}) }),
            precedence,
            in_main_token,
          }
        );
      },

      [this](const rules::Choice &choice) {
        for (const auto &element : choice.elements) {
          apply(element);
        }
      },

      [this](const rules::Seq &sequence) {
        TransitionMap left_transitions;
        TransitionBuilder(&left_transitions, this).apply(*sequence.left);

        for (const auto &pair : left_transitions) {
          add_transition(
            transitions,
            pair.first,
            transform_transition(pair.second, [&sequence](Rule rule) -> Rule {
              return Rule::seq({rule, *sequence.right});
            })
          );
        }

        if (rule_can_be_blank(*sequence.left)) {
          apply(*sequence.right);
        }
      },

      [this](const rules::Repeat &repeat) {
        TransitionMap content_transitions;
        TransitionBuilder(&content_transitions, this).apply(*repeat.rule);

        for (const auto &pair : content_transitions) {
          add_transition(transitions, pair.first, pair.second);
          add_transition(
            transitions, pair.first,
            transform_transition(pair.second, [&repeat](Rule item_rule) {
              return Rule::seq({ item_rule, repeat });
            })
          );
        }
      },

      [this](const rules::Metadata &metadata) {
        bool has_active_precedence = metadata.params.is_active;
        if (has_active_precedence)
          precedence_stack->push_back(metadata.params.precedence);

        if (metadata.params.is_main_token)
          in_main_token = true;

        auto params = metadata.params;
        if (params.has_precedence)
          params.is_active = true;

        TransitionMap content_transitions;
        TransitionBuilder(&content_transitions, this).apply(*metadata.rule);

        for (const auto &pair : content_transitions) {
          add_transition(
            transitions, pair.first,
            transform_transition(pair.second, [&params](Rule rule) {
              return rules::Metadata::merge(move(rule), params);
            })
          );
        }

        if (has_active_precedence) {
          precedence_stack->pop_back();
        }
      },

      [](auto) {}
    );
  }

  TransitionBuilder(TransitionMap *transitions, const rules::Symbol &item_lhs,
                    vector<int> *precedence_stack, bool in_main_token)
      : transitions(transitions),
        item_lhs(item_lhs),
        precedence_stack(precedence_stack),
        in_main_token(in_main_token) {}

  TransitionBuilder(TransitionMap *transitions, TransitionBuilder *other)
      : transitions(transitions),
        item_lhs(other->item_lhs),
        precedence_stack(other->precedence_stack),
        in_main_token(other->in_main_token) {}
};

void lex_item_transitions(TransitionMap *transitions, const LexItem &item) {
  vector<int> precedence_stack;
  TransitionBuilder(transitions, item.lhs, &precedence_stack, false).apply(item.rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
