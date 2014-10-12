#ifndef COMPILER_PREPARED_GRAMMAR_H_
#define COMPILER_PREPARED_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

class PreparedGrammar {
 public:
  PreparedGrammar();
  PreparedGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);

  const std::vector<std::pair<std::string, rules::rule_ptr>> rules;
  const std::vector<std::pair<std::string, rules::rule_ptr>> aux_rules;

  const std::string &rule_name(const rules::Symbol &symbol) const;
  const rules::rule_ptr &rule(const rules::Symbol &symbol) const;
};

class SyntaxGrammar : public PreparedGrammar {
 public:
  SyntaxGrammar();
  SyntaxGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);
  SyntaxGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules,
      const std::set<rules::Symbol> &ubiquitous_tokens);

  std::set<rules::Symbol> ubiquitous_tokens;
};

class LexicalGrammar : public PreparedGrammar {
 public:
  LexicalGrammar();
  LexicalGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);
  LexicalGrammar(
      const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
      const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules,
      const std::vector<rules::rule_ptr> &separators);

  std::vector<rules::rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_PREPARED_GRAMMAR_H_
