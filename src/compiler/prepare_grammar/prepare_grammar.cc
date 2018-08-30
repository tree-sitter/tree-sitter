#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/extract_simple_aliases.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/normalize_rules.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::get;
using std::move;

PrepareGrammarResult prepare_grammar(const InputGrammar &input_grammar) {
  PrepareGrammarResult result;

  // Convert all string-based `NamedSymbols` into numerical `Symbols`
  auto intern_result = intern_symbols(input_grammar);
  CompileError error = intern_result.second;
  if (error.type) {
    result.error = error;
    return result;
  }

  // Separate grammar into lexical and syntactic components
  auto extract_result = extract_tokens(intern_result.first);
  error = get<2>(extract_result);
  if (error.type) {
    result.error = error;
    return result;
  }

  // Replace `Repeat` rules with pairs of recursive rules
  InitialSyntaxGrammar syntax_grammar1 = expand_repeats(get<0>(extract_result));

  // Flatten syntax rules into lists of productions.
  auto flatten_result = flatten_grammar(syntax_grammar1);
  SyntaxGrammar syntax_grammar = flatten_result.first;
  error = flatten_result.second;
  if (error.type) {
    result.error = error;
    return result;
  }

  // Ensure all lexical rules are in a consistent format.
  LexicalGrammar lexical_grammar = normalize_rules(get<1>(extract_result));

  // Find any symbols that always have the same alias applied to them.
  // Remove those aliases since they can be applied in a simpler way.
  auto simple_aliases = extract_simple_aliases(&syntax_grammar, &lexical_grammar);

  return {
    move(syntax_grammar),
    move(lexical_grammar),
    move(simple_aliases),
    CompileError::none(),
  };
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
