#ifndef COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_

#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InitialSyntaxGrammar {
  std::vector<Variable> variables;
  std::set<rules::Symbol> extra_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
  std::set<rules::Symbol> variables_to_inline;
  rules::Symbol word_token;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INITIAL_SYNTAX_GRAMMAR_H_
