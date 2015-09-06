#ifndef COMPILER_PREPARED_GRAMMAR_H_
#define COMPILER_PREPARED_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

enum RuleEntryType {
  RuleEntryTypeNamed,
  RuleEntryTypeAnonymous,
  RuleEntryTypeHidden,
};

struct RuleEntry {
  std::string name;
  rule_ptr rule;
  RuleEntryType type;
};

class SyntaxGrammar {
 public:
  std::vector<RuleEntry> rules;
  std::set<rules::Symbol> ubiquitous_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
};

class LexicalGrammar {
 public:
  std::vector<RuleEntry> rules;
  std::vector<rule_ptr> separators;
};

}  // namespace tree_sitter

#endif  // COMPILER_PREPARED_GRAMMAR_H_
