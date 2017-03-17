#ifndef COMPILER_RULES_REPEAT_H_
#define COMPILER_RULES_REPEAT_H_

#include <memory>

namespace tree_sitter {
namespace rules {

struct Rule;

struct Repeat {
  std::shared_ptr<Rule> rule;

  explicit Repeat(const Rule &rule);
  bool operator==(const Repeat &other) const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_REPEAT_H_