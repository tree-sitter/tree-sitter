#ifndef COMPILER_SYNTAX_GRAMMAR_H_
#define COMPILER_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "compiler/rule.h"
#include "compiler/grammar.h"

namespace tree_sitter {

struct ProductionStep {
  rules::Symbol symbol;
  int precedence;
  rules::Associativity associativity;
  rules::Alias alias;

  bool operator==(const ProductionStep &) const;
  bool operator!=(const ProductionStep &) const;
  bool operator<(const ProductionStep &) const;
};

struct Production {
  std::vector<ProductionStep> steps;
  int dynamic_precedence;

  inline Production() : dynamic_precedence(0) {}

  inline Production(std::vector<ProductionStep> &&steps, int dynamic_precedence = 0) :
    steps(move(steps)), dynamic_precedence(dynamic_precedence) {}

  bool operator==(const Production &) const;
  inline ProductionStep &back() { return steps.back(); }
  inline const ProductionStep &back() const { return steps.back(); }
  inline bool empty() const { return steps.empty(); }
  inline size_t size() const { return steps.size(); }
  inline const ProductionStep &operator[](int i) const { return steps[i]; }
  inline const ProductionStep &at(int i) const { return steps[i]; }
  inline std::vector<ProductionStep>::const_iterator begin() const { return steps.begin(); }
  inline std::vector<ProductionStep>::const_iterator end() const { return steps.end(); }
};

struct SyntaxVariable {
  std::string name;
  VariableType type;
  std::vector<Production> productions;
};

struct ExternalToken {
  std::string name;
  VariableType type;
  rules::Symbol corresponding_internal_token;

  bool operator==(const ExternalToken &) const;
};

struct SyntaxGrammar {
  std::vector<SyntaxVariable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
  std::set<rules::Symbol> variables_to_inline;
  rules::Symbol word_token;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
