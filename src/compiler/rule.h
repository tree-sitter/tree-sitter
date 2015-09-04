#ifndef COMPILER_RULES_RULE_H_
#define COMPILER_RULES_RULE_H_

#include <string>
#include <memory>

namespace tree_sitter {

namespace rules {
class Visitor;
}  // namespace rules

class Rule;
typedef std::shared_ptr<Rule> rule_ptr;

class Rule {
 public:
  virtual bool operator==(const Rule &other) const = 0;
  bool operator!=(const Rule &other) const;
  virtual size_t hash_code() const = 0;
  virtual rule_ptr copy() const = 0;
  virtual std::string to_string() const = 0;
  virtual void accept(rules::Visitor *visitor) const = 0;
  virtual ~Rule();
};

std::ostream &operator<<(std::ostream &stream, const Rule &rule);
std::ostream &operator<<(std::ostream &stream, const rule_ptr &rule);

}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::rule_ptr> {
  size_t operator()(const tree_sitter::rule_ptr &rule) const {
    return typeid(*rule).hash_code() ^ rule->hash_code();
  }
};

}  // namespace std

#endif  // COMPILER_RULES_RULE_H_
