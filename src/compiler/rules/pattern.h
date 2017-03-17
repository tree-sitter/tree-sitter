#ifndef COMPILER_RULES_PATTERN_H_
#define COMPILER_RULES_PATTERN_H_

#include <string>

namespace tree_sitter {
namespace rules {

struct Pattern {
  std::string value;

  inline bool operator==(const Pattern &other) const {
    return value == other.value;
  }
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_PATTERN_H_