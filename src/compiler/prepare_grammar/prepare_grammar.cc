#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/normalize_rules.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::tuple;
using std::get;
using std::make_tuple;

tuple<SyntaxGrammar, LexicalGrammar, CompileError> prepare_grammar(
  const InputGrammar &input_grammar) {
  /*
   * Convert all string-based `NamedSymbols` into numerical `Symbols`
   */
  auto intern_result = intern_symbols(input_grammar);
  CompileError error = intern_result.second;
  if (error.type)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  /*
   * Separate grammar into lexical and syntactic components
   */
  auto extract_result = extract_tokens(intern_result.first);
  error = get<2>(extract_result);
  if (error.type) {
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);
  }

  /*
   * Replace `Repeat` rules with pairs of recursive rules
   */
  InitialSyntaxGrammar syntax_grammar1 = expand_repeats(get<0>(extract_result));

  /*
   * Expand `String` and `Pattern` rules into full rule trees
   */
  LexicalGrammar lex_grammar = get<1>(extract_result);
  // auto expand_tokens_result = expand_tokens(get<1>(extract_result));
  // LexicalGrammar lex_grammar = expand_tokens_result.first;
  // error = expand_tokens_result.second;
  // if (error.type)
  //   return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  /*
   * Flatten syntax rules into lists of productions.
   */
  auto flatten_result = flatten_grammar(syntax_grammar1);
  SyntaxGrammar syntax_grammar = flatten_result.first;
  error = flatten_result.second;
  if (error.type)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  /*
   * Ensure all lexical rules are in a consistent format.
   */
  lex_grammar = normalize_rules(lex_grammar);

  return make_tuple(syntax_grammar, lex_grammar, CompileError::none());
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
