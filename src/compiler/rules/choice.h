#ifndef COMPILER_RULES_CHOICE_H_
#define COMPILER_RULES_CHOICE_H_

#include <memory>
#include <vector>

namespace tree_sitter {
namespace rules {

struct Rule;

struct Choice {
  std::vector<Rule> elements;

  bool operator==(const Choice &other) const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_CHOICE_H_