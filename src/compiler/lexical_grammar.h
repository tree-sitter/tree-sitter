#ifndef COMPILER_LEXICAL_GRAMMAR_H_
#define COMPILER_LEXICAL_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/variable.h"

namespace tree_sitter {

struct LexicalVariable {
  std::string name;
  VariableType type;
  rule_ptr rule;
  bool is_string;
};

struct LexicalGrammar {
  std::vector<LexicalVariable> variables;
  std::vector<rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEXICAL_GRAMMAR_H_
