#ifndef COMPILER_LEXICAL_GRAMMAR_H_
#define COMPILER_LEXICAL_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/grammar.h"

namespace tree_sitter {

struct LexicalVariable {
  std::string name;
  VariableType type;
  rules::Rule rule;
  bool is_string;

  inline bool operator==(const LexicalVariable &other) const {
    return other.name == name && other.type == type && other.rule == rule &&
      other.is_string == is_string;
  }
};

struct LexicalGrammar {
  std::vector<LexicalVariable> variables;
  std::vector<rules::Rule> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEXICAL_GRAMMAR_H_
