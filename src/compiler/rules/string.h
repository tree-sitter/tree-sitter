#ifndef COMPILER_RULES_STRING_H_
#define COMPILER_RULES_STRING_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class String : public Rule {
 public:
  explicit String(std::string value);

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  const std::string value;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_STRING_H_
