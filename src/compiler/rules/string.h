#ifndef COMPILER_RULES_STRING_H_
#define COMPILER_RULES_STRING_H_

#include <string>

namespace tree_sitter {
namespace rules {

struct String {
  std::string value;

  inline bool operator==(const String &other) const {
    return value == other.value;
  }
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_STRING_H_