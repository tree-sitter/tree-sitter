#ifndef COMPILER_SYNTAX_GRAMMAR_H_
#define COMPILER_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/grammar.h"

namespace tree_sitter {

struct ProductionStep {
  inline bool operator==(const ProductionStep &other) const {
    return symbol == other.symbol && precedence == other.precedence &&
           associativity == other.associativity;
  }

  rules::Symbol symbol;
  int precedence;
  rules::Associativity associativity;
};

typedef std::vector<ProductionStep> Production;

struct SyntaxVariable {
  std::string name;
  VariableType type;
  std::vector<Production> productions;
};

using ConflictSet = std::set<rules::Symbol>;

struct SyntaxGrammar {
  std::vector<SyntaxVariable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<ConflictSet> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
