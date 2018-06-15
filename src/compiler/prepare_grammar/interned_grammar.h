#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InternedGrammar {
  std::vector<Variable> variables;
  std::vector<rules::Rule> extra_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
  std::vector<Variable> external_tokens;
  std::set<rules::Symbol> variables_to_inline;
  rules::Symbol word_token;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
