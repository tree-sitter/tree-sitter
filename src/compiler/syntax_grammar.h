#ifndef COMPILER_SYNTAX_GRAMMAR_H_
#define COMPILER_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

class SyntaxGrammar {
 public:
  const std::string &rule_name(const rules::Symbol &symbol) const;
  const rules::rule_ptr &rule(const rules::Symbol &symbol) const;

  std::vector<std::pair<std::string, rules::rule_ptr>> rules;
  std::vector<std::pair<std::string, rules::rule_ptr>> aux_rules;
  std::set<rules::Symbol> ubiquitous_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
};

}  // namespace tree_sitter

#endif  // COMPILER_SYNTAX_GRAMMAR_H_
