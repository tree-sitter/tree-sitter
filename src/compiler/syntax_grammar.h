#ifndef COMPILER_SYNTAX_GRAMMAR_H_
#define COMPILER_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/variable.h"

namespace tree_sitter {

struct ExternalToken {
  std::string name;
  VariableType type;
};

struct ProductionStep {
  ProductionStep(const rules::Symbol &, int, rules::Associativity);
  bool operator==(const ProductionStep &) const;

  rules::Symbol symbol;
  int precedence;
  rules::Associativity associativity;
};

typedef std::vector<ProductionStep> Production;

struct SyntaxVariable {
  SyntaxVariable(const std::string &, VariableType,
                 const std::vector<Production> &);

  std::string name;
  std::vector<Production> productions;
  VariableType type;
};

typedef std::set<rules::Symbol> ConflictSet;

struct SyntaxGrammar {
  std::vector<SyntaxVariable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<ConflictSet> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
