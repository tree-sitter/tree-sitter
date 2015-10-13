#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

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

}  // namespace tree_sitter

#endif  // COMPILER_VARIABLE_H_
