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
