#ifndef COMPILER_LEXICAL_GRAMMAR_H_
#define COMPILER_LEXICAL_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/variable.h"

namespace tree_sitter {

struct LexicalVariable {
  LexicalVariable(const std::string &, VariableType, const rule_ptr &, bool);

  std::string name;
  rule_ptr rule;
  VariableType type;
  bool is_string;
};

struct LexicalGrammar {
  std::vector<LexicalVariable> variables;
  std::vector<rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEXICAL_GRAMMAR_H_
