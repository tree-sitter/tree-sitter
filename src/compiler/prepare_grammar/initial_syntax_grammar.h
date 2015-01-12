#ifndef COMPILER_INITIAL_SYNTAX_GRAMMAR_H_
#define COMPILER_INITIAL_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace prepare_grammar {

class InitialSyntaxGrammar {
 public:
  InitialSyntaxGrammar();
  InitialSyntaxGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);
  InitialSyntaxGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules,
      const std::set<rules::Symbol> &ubiquitous_tokens);

  const std::string &rule_name(const rules::Symbol &symbol) const;
  const rules::rule_ptr &rule(const rules::Symbol &symbol) const;

  const std::vector<std::pair<std::string, rules::rule_ptr>> rules;
  const std::vector<std::pair<std::string, rules::rule_ptr>> aux_rules;
  std::set<rules::Symbol> ubiquitous_tokens;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_INITIAL_SYNTAX_GRAMMAR_H_
