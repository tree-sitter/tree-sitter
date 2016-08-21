#ifndef COMPILER_GRAMMAR_H_
#define COMPILER_GRAMMAR_H_

#include <vector>
#include <string>
#include <utility>
#include "compiler/rule.h"

namespace tree_sitter {

enum VariableType {
  VariableTypeHidden,
  VariableTypeAuxiliary,
  VariableTypeAnonymous,
  VariableTypeNamed,
};

struct Variable {
  Variable(const std::string &, VariableType, const rule_ptr &);

  std::string name;
  rule_ptr rule;
  VariableType type;
};

struct Grammar {
  std::vector<Variable> variables;
  std::vector<rule_ptr> extra_tokens;
  std::vector<std::vector<std::string>> expected_conflicts;
};

}  // namespace tree_sitter

#endif  // COMPILER_GRAMMAR_H_
