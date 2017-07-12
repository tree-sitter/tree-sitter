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
    return symbol == other.symbol &&
      precedence == other.precedence &&
      associativity == other.associativity;
  }

  inline bool operator!=(const ProductionStep &other) const {
    return !operator==(other);
  }

  inline bool operator<(const ProductionStep &other) const {
    if (symbol < other.symbol) return true;
    if (other.symbol < symbol) return false;
    if (precedence < other.precedence) return true;
    if (other.precedence < precedence) return false;
    return associativity < other.associativity;
  }

  rules::Symbol symbol;
  int precedence;
  rules::Associativity associativity;
};

struct Production {
  std::vector<ProductionStep> steps;
  int dynamic_precedence = 0;

  inline bool operator==(const Production &other) const {
    return steps == other.steps && dynamic_precedence == other.dynamic_precedence;
  }

  inline ProductionStep &back() { return steps.back(); }
  inline const ProductionStep &back() const { return steps.back(); }
  inline bool empty() const { return steps.empty(); }
  inline size_t size() const { return steps.size(); }
  inline const ProductionStep &operator[](int i) const { return steps[i]; }
  inline const ProductionStep &at(int i) const { return steps[i]; }
};

struct SyntaxVariable {
  std::string name;
  VariableType type;
  std::vector<Production> productions;
};

using ConflictSet = std::set<rules::Symbol>;

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

struct SyntaxGrammar {
  std::vector<SyntaxVariable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<ConflictSet> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
