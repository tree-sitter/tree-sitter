#ifndef COMPILER_RULES_PATTERN_H_
#define COMPILER_RULES_PATTERN_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class Pattern : public Rule {
 public:
  explicit Pattern(const std::string &string);

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  const std::string value;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_PATTERN_H_
