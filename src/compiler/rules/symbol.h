#ifndef COMPILER_RULES_SYMBOL_H_
#define COMPILER_RULES_SYMBOL_H_

#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

class Symbol : public Rule {
 public:
  typedef int Index;

  typedef enum {
    Terminal,
    NonTerminal,
    External,
  } Type;

  Symbol(Index index, Type type);

  bool operator==(const Symbol &other) const;
  bool operator==(const Rule &other) const;

  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  bool operator<(const Symbol &other) const;
  static bool is_built_in(Index);
  bool is_built_in() const;
  bool is_token() const;
  bool is_external() const;
  bool is_non_terminal() const;

  Index index;
  Type type;
};

}  // namespace rules
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::rules::Symbol> {
  size_t operator()(const tree_sitter::rules::Symbol &rule) const {
    return rule.hash_code();
  }
};

}  // std

#endif  // COMPILER_RULES_SYMBOL_H_
