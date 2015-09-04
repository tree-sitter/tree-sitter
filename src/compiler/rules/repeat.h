#ifndef COMPILER_RULES_REPEAT_H_
#define COMPILER_RULES_REPEAT_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class Repeat : public Rule {
 public:
  explicit Repeat(rule_ptr content);
  static rule_ptr build(const rule_ptr &rule);

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  const rule_ptr content;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_REPEAT_H_
