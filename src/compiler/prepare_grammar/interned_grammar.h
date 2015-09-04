#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <string>
#include <set>
#include <utility>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InternedGrammar {
  std::vector<std::pair<std::string, rule_ptr>> rules;
  std::set<rule_ptr> ubiquitous_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
