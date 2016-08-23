#ifndef COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_

#include <vector>
#include <string>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"
#include "compiler/grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InitialSyntaxGrammar {
  std::vector<Variable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<ConflictSet> expected_conflicts;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_
