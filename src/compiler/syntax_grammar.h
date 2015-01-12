#ifndef COMPILER_SYNTAX_GRAMMAR_H_
#define COMPILER_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

struct ProductionEntry {
  rules::Symbol symbol;
  int precedence;
  int rule_id;

  bool operator==(const ProductionEntry &) const;
};

class Production {
public:
  std::vector<ProductionEntry> entries;
  int end_rule_id;
  Production(const std::vector<ProductionEntry> &, int);
  size_t size() const;
  const rules::Symbol &symbol_at(size_t) const;
  int precedence_at(size_t) const;
  int rule_id_at(size_t) const;
};

std::ostream &operator<<(std::ostream &, const ProductionEntry &);
std::ostream &operator<<(std::ostream &, const Production &);

class SyntaxGrammar {
 public:
  SyntaxGrammar();
  SyntaxGrammar(
      const std::vector<std::pair<std::string, std::vector<Production>>> &rules,
      const std::vector<std::pair<std::string, std::vector<Production>>> &aux_rules,
      const std::set<rules::Symbol> &ubiquitous_tokens);

  const std::string &rule_name(const rules::Symbol &symbol) const;
  const std::vector<Production> &productions(const rules::Symbol &) const;

  std::vector<std::pair<std::string, std::vector<Production>>> rules;
  std::vector<std::pair<std::string, std::vector<Production>>> aux_rules;
  std::set<rules::Symbol> ubiquitous_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
