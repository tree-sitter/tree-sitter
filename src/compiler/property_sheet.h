#ifndef COMPILER_PROPERTY_SHEET_H_
#define COMPILER_PROPERTY_SHEET_H_

#include <vector>
#include <map>
#include <string>

namespace tree_sitter {

struct PropertySelectorStep {
  std::string type;
  bool named;
  bool is_immediate;
  int index;
  std::string text_pattern;

  inline bool operator==(const PropertySelectorStep &other) const {
    return
      type == other.type &&
      named == other.named &&
      is_immediate == other.is_immediate &&
      index == other.index;
  }
};

typedef std::vector<PropertySelectorStep> PropertySelector;

typedef std::map<std::string, std::string> PropertySet;

struct PropertyRule {
  std::vector<PropertySelector> selectors;
  PropertySet properties;
};

typedef std::vector<PropertyRule> PropertySheet;

}  // namespace tree_sitter

#endif  // COMPILER_PROPERTY_SHEET_H_
