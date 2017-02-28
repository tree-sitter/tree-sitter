#include "compiler/prepare_grammar/normalize_rules.h"
#include "compiler/prepare_grammar/extract_choices.h"
#include "compiler/rules/choice.h"

namespace tree_sitter {
namespace prepare_grammar {

LexicalGrammar normalize_rules(const LexicalGrammar &input_grammar) {
  LexicalGrammar result(input_grammar);

  for (LexicalVariable &variable : result.variables) {
    variable.rule = rules::Choice::build(extract_choices(variable.rule));
  }

  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
