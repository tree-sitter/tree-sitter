#include <vector>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include "compiler/property_sheet.h"
#include "compiler/property_table.h"
#include "compiler/build_tables/property_table_builder.h"
#include "compiler/util/hash_combine.h"

using std::deque;
using std::vector;
using std::pair;
using std::unordered_map;
using std::set;
using std::move;
using std::map;

namespace tree_sitter {
namespace build_tables {

// A position within a selector for a particular rule set.
// For example, in a selector like `a > b`, this might
// describe the state of having descended into an `a`,
// but not a `b`.
struct PropertyItem {
  unsigned rule_id;
  unsigned selector_id;
  unsigned step_id;

  bool operator==(const PropertyItem &other) const {
    return
      rule_id == other.rule_id &&
      selector_id == other.selector_id &&
      step_id == other.step_id;
  }

  bool operator<(const PropertyItem &other) const {
    if (rule_id < other.rule_id) return true;
    if (rule_id > other.rule_id) return false;
    if (selector_id < other.selector_id) return true;
    if (selector_id > other.selector_id) return false;
    return step_id < other.step_id;
  }
};

// A set of possible positions within different selectors.
// This directly represents a state of the property-matching
// state machine.
struct PropertyItemSet {
  set<PropertyItem> entries;

  bool operator==(const PropertyItemSet &other) const {
    return entries == other.entries;
  }
};

// A set of properties that matched via a certain selector.
// These are ordered according to the usual CSS rules:
// specificity, falling back to the order in the original sheet.
struct PropertySelectorMatch {
  unsigned specificity;
  unsigned rule_id;
  unsigned selector_id;
  const PropertySet *property_set;

  bool operator<(const PropertySelectorMatch &other) const {
    if (specificity < other.specificity) return true;
    if (specificity > other.specificity) return false;
    if (rule_id < other.rule_id) return true;
    if (rule_id > other.rule_id) return false;
    return selector_id < other.selector_id;
  }
};

struct PropertyTransitionEntry {
  PropertyTransition transition;
  unsigned latest_matching_rule_id;

  unsigned specificity() const {
    return
      (transition.index == -1 ? 0 : 1) +
      (transition.text_pattern.empty() ? 0 : 1);
  }

  // When using the final state machine, the runtime library computes
  // a node's property by descending from the root of the syntax
  // tree to that node. For each ancestor node on the way, it should
  // update its state using the *first* matching entry of the
  // `transitions` list. Therefore, the order of the transitions
  // must match the normal tie-breaking rules of CSS.
  bool operator<(const PropertyTransitionEntry &other) const {
    // If two transitions match different node types, they can't
    // both match a given node, so their order is arbitrary.
    if (transition.type < other.transition.type) return true;
    if (transition.type > other.transition.type) return false;
    if (transition.named && !other.transition.named) return true;
    if (!transition.named && other.transition.named) return false;

    // More specific transitions should be considered before less
    // specific ones.
    if (specificity() > other.specificity()) return true;
    if (specificity() < other.specificity()) return false;

    // If there are two transitions with a specificity tie (e.g. one
    // with an `:nth-child` pseudo-class and a one with a `:text`
    // pseudo-class), then the one whose matching properties appeared
    // later in the cascade should be considered first.
    return latest_matching_rule_id > other.latest_matching_rule_id;
  }
};

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::util::hash_combine;

// PropertyItemSets must be hashed because in the process of building
// the table, we maintain a map of existing property item sets to
// state ids.
template <>
struct hash<tree_sitter::build_tables::PropertyItemSet> {
  size_t operator()(const tree_sitter::build_tables::PropertyItemSet &item_set) const {
    size_t result = 0;
    hash_combine(&result, item_set.entries.size());
    for (const auto &item : item_set.entries) {
      hash_combine(&result, item.rule_id);
      hash_combine(&result, item.selector_id);
      hash_combine(&result, item.step_id);
    }
    return result;
  }
};

// PropertyTransitions must be hashed because we represent state
// transitions as a map of PropertyTransitions to successor PropertyItemSets.
template <>
struct hash<tree_sitter::PropertyTransition> {
  size_t operator()(const tree_sitter::PropertyTransition &transition) const {
    size_t result = 0;
    hash_combine(&result, transition.type);
    hash_combine(&result, transition.named);
    hash_combine(&result, transition.index);
    hash_combine(&result, transition.text_pattern);
    hash_combine(&result, transition.state_id);
    return result;
  }
};

// PropertySets must be hashed so that we can use a map to dedup them.
template <>
struct hash<tree_sitter::PropertySet> {
  size_t operator()(const tree_sitter::PropertySet &set) const {
    size_t result = 0;
    hash_combine(&result, set.size());
    for (const auto &pair : set) {
      hash_combine(&result, pair.first);
      hash_combine(&result, pair.second);
    }
    return result;
  }
};

}  // namespace std

namespace tree_sitter {
namespace build_tables {

typedef unsigned StateId;
typedef unsigned PropertySetId;

struct PropertyTableBuilder {
  PropertySheet sheet;
  PropertyTable result;
  unordered_map<PropertyItemSet, StateId> ids_by_item_set;
  unordered_map<PropertySet, PropertySetId> ids_by_property_set;
  deque<pair<PropertyItemSet, StateId>> item_set_queue;

  PropertyTableBuilder(const PropertySheet &sheet) : sheet(sheet) {}

  PropertyTable build() {
    PropertyItemSet start_item_set;
    for (unsigned i = 0; i < sheet.size(); i++) {
      PropertyRule &rule = sheet[i];
      for (unsigned j = 0; j < rule.selectors.size(); j++) {
        start_item_set.entries.insert(PropertyItem {i, j, 0});
      }
    }

    add_state(start_item_set);
    while (!item_set_queue.empty()) {
      auto entry = item_set_queue.front();
      PropertyItemSet item_set = move(entry.first);
      StateId state_id = entry.second;
      item_set_queue.pop_front();
      populate_state(item_set, state_id);
    }

    remove_duplicate_states();

    return result;
  }

  // Different item sets can actually produce the same state, so the
  // states need to be explicitly deduped as a post-processing step.
  void remove_duplicate_states() {
    map<StateId, StateId> replacements;

    while (true) {
      map<StateId, StateId> duplicates;
      for (StateId i = 0, size = result.states.size(); i < size; i++) {
        for (StateId j = 0; j < i; j++) {
          if (!duplicates.count(j) && result.states[j] == result.states[i]) {
            duplicates.insert({ i, j });
            break;
          }
        }
      }

      if (duplicates.empty()) break;

      map<StateId, StateId> new_replacements;
      for (StateId i = 0, size = result.states.size(); i < size; i++) {
        StateId new_state_index = i;
        auto duplicate = duplicates.find(i);
        if (duplicate != duplicates.end()) {
          new_state_index = duplicate->second;
        }

        size_t prior_removed = 0;
        for (const auto &duplicate : duplicates) {
          if (duplicate.first >= new_state_index) break;
          prior_removed++;
        }

        new_state_index -= prior_removed;
        new_replacements.insert({i, new_state_index});
        replacements.insert({ i, new_state_index });
        for (auto &replacement : replacements) {
          if (replacement.second == i) {
            replacement.second = new_state_index;
          }
        }
      }

      for (auto &state : result.states) {
        for (auto &transition : state.transitions) {
          auto new_replacement = new_replacements.find(transition.state_id);
          if (new_replacement != new_replacements.end()) {
            transition.state_id = new_replacement->second;
          }
        }

        auto new_replacement = new_replacements.find(state.default_next_state_id);
        if (new_replacement != new_replacements.end()) {
          state.default_next_state_id = new_replacement->second;
        }
      }

      for (auto i = duplicates.rbegin(); i != duplicates.rend(); ++i) {
        result.states.erase(result.states.begin() + i->first);
      }
    }
  }

  // Get the next part of the selector that needs to be matched for a given item.
  // This returns null if the item has consumed its entire selector.
  const PropertySelectorStep *next_step_for_item(const PropertyItem &item) {
    const PropertySelector &selector = sheet[item.rule_id].selectors[item.selector_id];
    if (item.step_id < selector.size()) {
      return &selector[item.step_id];
    } else {
      return nullptr;
    }
  }

  // Get the previous part of the selector that was matched for a given item.
  // This returns null if the item has not consumed anything.
  const PropertySelectorStep *prev_step_for_item(const PropertyItem &item) {
    if (item.step_id > 0) {
      return &sheet[item.rule_id].selectors[item.selector_id][item.step_id];
    } else {
      return nullptr;
    }
  }

  unsigned specificity_for_selector(const PropertySelector &selector) {
    unsigned result = selector.size();
    for (const PropertySelectorStep &step : selector) {
      if (step.index != -1) result++;
      if (!step.text_pattern.empty()) result++;
    }
    return result;
  }

  // Check if the given state transition matches the given part of a selector.
  bool step_matches_transition(const PropertySelectorStep &step, const PropertyTransition &transition) {
    return
      step.type == transition.type &&
      step.named == transition.named &&
      (step.index == transition.index || step.index == -1) &&
      (step.text_pattern == transition.text_pattern || step.text_pattern.empty());
  }

  void populate_state(const PropertyItemSet &item_set, StateId state_id) {
    unordered_map<PropertyTransition, PropertyItemSet> transitions;
    vector<PropertySelectorMatch> selector_matches;

    for (const PropertyItem &item : item_set.entries) {
      const PropertySelectorStep *next_step = next_step_for_item(item);

      // If this item has more elements to match for its selector, then
      // there's a state transition for elements that match the next
      // part of the selector.
      if (next_step) {
        transitions[PropertyTransition{
          next_step->type,
          next_step->named,
          next_step->index,
          next_step->text_pattern,
          0
        }] = PropertyItemSet();
      }

      // If the item has matched its entire selector, then the property set
      // for the item's rule applies in this state.
      else {
        const PropertyRule &rule = sheet[item.rule_id];
        selector_matches.push_back(PropertySelectorMatch {
          specificity_for_selector(rule.selectors[item.selector_id]),
          item.rule_id,
          item.selector_id,
          &rule.properties,
        });
      }
    }

    // For each element that follows an item in this set,
    // compute the next item set after descending through that element.
    vector<PropertyTransitionEntry> transition_list;
    for (auto &pair : transitions) {
      PropertyTransition transition = pair.first;
      PropertyItemSet &next_item_set = pair.second;
      unsigned latest_matching_rule_id = 0;

      for (const PropertyItem &item : item_set.entries) {
        const PropertySelectorStep *next_step = next_step_for_item(item);
        const PropertySelectorStep *prev_step = prev_step_for_item(item);
        if (next_step) {

          // If the element matches the next part of the item, advance the
          // item to the next part of its selector.
          if (step_matches_transition(*next_step, transition)) {
            PropertyItem next_item = item;
            next_item.step_id++;
            next_item_set.entries.insert(next_item);

            // If the item is at the end of its selector, record its rule id
            // so that it can be used when sorting the transitions.
            if (!next_step_for_item(next_item) && next_item.rule_id > latest_matching_rule_id) {
              latest_matching_rule_id = item.rule_id;
            }
          }

          // If the element does not match, and the item is in the middle
          // of an immediate child selector, then remove it from the
          // next item set. Otherwise, keep it unchanged.
          if (!prev_step || !prev_step->is_immediate) {
            next_item_set.entries.insert(item);
          }
        }
      }

      transition.state_id = add_state(next_item_set);
      transition_list.push_back(PropertyTransitionEntry {transition, latest_matching_rule_id});
    }

    std::sort(transition_list.begin(), transition_list.end());
    for (auto &entry : transition_list) {
      result.states[state_id].transitions.push_back(entry.transition);
    }

    // Compute the default successor item set - the item set that
    // we should advance to if the next element doesn't match any
    // of the next elements in the item set's selectors.
    PropertyItemSet default_next_item_set;
    for (const PropertyItem &item : item_set.entries) {
      const PropertySelectorStep *next_step = next_step_for_item(item);
      const PropertySelectorStep *prev_step = prev_step_for_item(item);
      if (next_step && (!prev_step || !prev_step->is_immediate)) {
        default_next_item_set.entries.insert(item);
      }
    }

    StateId default_next_state_id = add_state(default_next_item_set);
    result.states[state_id].default_next_state_id = default_next_state_id;

    // Sort the matching property sets by ascending specificity and by
    // their order in the sheet. This way, more specific selectors and later
    // rules will override less specific selectors and earlier rules.
    PropertySet properties;
    std::sort(selector_matches.begin(), selector_matches.end());
    for (auto &match : selector_matches) {
      for (auto &pair : *match.property_set) {
        properties[pair.first] = pair.second;
      }
    }

    // Add the final property set to the deduped list.
    result.states[state_id].property_set_id = add_property_set(properties);
  }

  StateId add_state(const PropertyItemSet &item_set) {
    auto entry = ids_by_item_set.find(item_set);
    if (entry == ids_by_item_set.end()) {
      StateId id = result.states.size();
      ids_by_item_set[item_set] = id;
      result.states.push_back(PropertyState {});
      item_set_queue.push_back({item_set, id});
      return id;
    } else {
      return entry->second;
    }
  }

  PropertySetId add_property_set(const PropertySet &property_set) {
    auto entry = ids_by_property_set.find(property_set);
    if (entry == ids_by_property_set.end()) {
      PropertySetId id = result.property_sets.size();
      ids_by_property_set[property_set] = id;
      result.property_sets.push_back(property_set);
      return id;
    } else {
      return entry->second;
    }
  }
};

PropertyTable build_property_table(const PropertySheet &sheet) {
  return PropertyTableBuilder(sheet).build();
}

}  // namespace build_tables
}  // namespace tree_sitter
