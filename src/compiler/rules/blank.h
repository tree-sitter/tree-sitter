#ifndef COMPILER_RULES_BLANK_H_
#define COMPILER_RULES_BLANK_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class Blank : public Rule {
 public:
  Blank();
  static rule_ptr build();

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_BLANK_H_
