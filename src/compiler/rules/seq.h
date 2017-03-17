#ifndef COMPILER_RULES_SEQ_H_
#define COMPILER_RULES_SEQ_H_

#include <memory>
#include <vector>

namespace tree_sitter {
namespace rules {

struct Rule;

struct Seq {
  std::shared_ptr<Rule> left;
  std::shared_ptr<Rule> right;

  Seq(const Rule &left, const Rule &right);
  bool operator==(const Seq &other) const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_SEQ_H_