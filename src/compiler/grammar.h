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

struct ExternalToken {
  std::string name;
  VariableType type;
  rules::Symbol corresponding_internal_token;

  inline bool operator==(const ExternalToken &other) const {
    return name == other.name &&
      type == other.type &&
      corresponding_internal_token == other.corresponding_internal_token;
  }
};

struct InputGrammar {
  struct Variable {
    std::string name;
    VariableType type;
    rules::Rule rule;
  };

  std::vector<Variable> variables;
  std::vector<rules::Rule> extra_tokens;
  std::vector<std::unordered_set<rules::NamedSymbol>> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_GRAMMAR_H_
