#ifndef COMPILER_LEXICAL_GRAMMAR_H_
#define COMPILER_LEXICAL_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/variable.h"

namespace tree_sitter {

struct LexicalGrammar {
  std::vector<Variable> variables;
  std::vector<rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEXICAL_GRAMMAR_H_
