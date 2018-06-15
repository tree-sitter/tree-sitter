#ifndef COMPILER_GRAMMAR_H_
#define COMPILER_GRAMMAR_H_

#include <vector>
#include <unordered_set>
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
  std::string name;
  VariableType type;
  rules::Rule rule;

  inline bool operator==(const Variable &other) const {
    return name == other.name && rule == other.rule && type == other.type;
  }
};

struct InputGrammar {
  std::vector<Variable> variables;
  std::vector<rules::Rule> extra_tokens;
  std::vector<std::unordered_set<rules::NamedSymbol>> expected_conflicts;
  std::vector<rules::Rule> external_tokens;
  std::unordered_set<rules::NamedSymbol> variables_to_inline;
  rules::NamedSymbol word_token;
};

}  // namespace tree_sitter

#endif  // COMPILER_GRAMMAR_H_
