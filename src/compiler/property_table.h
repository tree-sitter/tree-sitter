#ifndef COMPILER_PROPERTY_TABLE_H_
#define COMPILER_PROPERTY_TABLE_H_

#include <vector>
#include <map>
#include <string>
#include "compiler/property_sheet.h"

namespace tree_sitter {

struct PropertyTransition {
  std::string type;
  bool named;
  int index;
  std::string text_pattern;
  unsigned state_id;

  bool operator==(const PropertyTransition &other) const {
    return
      type == other.type &&
      named == other.named &&
      index == other.index &&
      text_pattern == other.text_pattern &&
      state_id == other.state_id;
  }

  bool operator<(const PropertyTransition &other) const {
    if (type < other.type) return true;
    if (type > other.type) return false;
    if (named && !other.named) return true;
    if (!named && other.named) return false;

    // The lack of a specific child index is represented as -1.
    // It should be sorted *after* transitions with a specific
    // child index.
    if (index > other.index) return true;
    if (index < other.index) return false;

    // The lack of a text pattern is represented as the empty string.
    // This should be sorted *after* transitions with a specific
    // text pattern.
    if (text_pattern.size() > other.text_pattern.size()) return true;
    if (text_pattern.size() < other.text_pattern.size()) return false;

    return state_id < other.state_id;
  }
};

struct PropertyState {
  std::vector<PropertyTransition> transitions;
  unsigned default_next_state_id;
  unsigned property_set_id;

  bool operator==(const PropertyState &other) const {
    return
      transitions == other.transitions &&
      default_next_state_id == other.default_next_state_id &&
      property_set_id == other.property_set_id;
  }
};

struct PropertyTable {
  std::vector<PropertyState> states;
  std::vector<PropertySet> property_sets;
};

}  // namespace tree_sitter

#endif  // COMPILER_PROPERTY_TABLE_H_
