#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

struct InternedExternalToken {
  std::string name;
  VariableType type;
  rules::Rule rule;
  bool can_be_blank;

  bool operator==(const InternedExternalToken &other) const {
    return name == other.name &&
      type == other.type &&
      rule == other.rule &&
      can_be_blank == other.can_be_blank;
  }
};

struct InternedGrammar {
  std::vector<Variable> variables;
  std::vector<rules::Rule> extra_tokens;
  std::set<std::set<rules::Symbol>> expected_conflicts;
  std::vector<InternedExternalToken> external_tokens;
  std::set<rules::Symbol> blank_external_tokens;
  std::set<rules::Symbol> variables_to_inline;
};

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
