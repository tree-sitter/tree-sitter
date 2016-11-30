#ifndef COMPILER_RULES_EXTERNAL_TOKEN_H_
#define COMPILER_RULES_EXTERNAL_TOKEN_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class ExternalToken : public Rule {
 public:
  explicit ExternalToken(const std::string &);
  static rule_ptr build(const std::string &);

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  std::string name;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_EXTERNAL_TOKEN_H_
