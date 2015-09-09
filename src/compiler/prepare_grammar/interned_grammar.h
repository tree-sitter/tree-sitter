#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InternedGrammar {
  std::vector<RuleEntry> rules;
  std::vector<rule_ptr> ubiquitous_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
