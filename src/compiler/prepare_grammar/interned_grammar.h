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
  struct Variable {
    std::string name;
    VariableType type;
    rules::Rule rule;

    bool operator==(const Variable &other) const {
      return name == other.name && type == other.type && rule == other.rule;
    }
  };

  std::vector<Variable> variables;
  std::vector<rules::Rule> extra_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
  std::vector<ExternalToken> external_tokens;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
