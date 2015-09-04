#ifndef COMPILER_LEXICAL_GRAMMAR_H_
#define COMPILER_LEXICAL_GRAMMAR_H_

#include <vector>
#include <string>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

class LexicalGrammar {
 public:
  const std::string &rule_name(const rules::Symbol &symbol) const;
  const rule_ptr &rule(const rules::Symbol &symbol) const;

  std::vector<std::pair<std::string, rule_ptr>> rules;
  std::vector<std::pair<std::string, rule_ptr>> aux_rules;
  std::vector<rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEXICAL_GRAMMAR_H_
