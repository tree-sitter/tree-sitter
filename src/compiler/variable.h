#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <string>
#include "compiler/rule.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

enum VariableType {
  VariableTypeHidden,
  VariableTypeAuxiliary,
  VariableTypeAnonymous,
  VariableTypeNamed,
};

struct Variable {
  std::string name;
  VariableType type;
  rule_ptr rule;
};

}  // namespace tree_sitter

#endif  // COMPILER_VARIABLE_H_
