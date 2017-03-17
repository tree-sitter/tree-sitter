#ifndef COMPILER_RULES_BLANK_H_
#define COMPILER_RULES_BLANK_H_

namespace tree_sitter {
namespace rules {

struct Blank {
  inline bool operator==(const Blank &other) const {
    return true;
  }
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_BLANK_H_