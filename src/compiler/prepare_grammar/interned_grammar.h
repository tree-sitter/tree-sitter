#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"
#include "compiler/syntax_grammar.h"
#include "compiler/variable.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InternedGrammar {
  std::vector<Variable> variables;
  std::vector<rule_ptr> extra_tokens;
  std::set<ConflictSet> expected_conflicts;
  std::vector<std::string> external_tokens;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
