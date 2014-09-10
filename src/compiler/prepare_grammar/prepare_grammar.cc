#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/intern_symbols.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::tuple;
using std::get;
using std::make_tuple;

tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *> prepare_grammar(
    const Grammar &input_grammar) {

  // Convert all string-based `NamedSymbols` into numerical `Symbols`
  auto intern_result = intern_symbols(input_grammar);
  const GrammarError *error = intern_result.second;
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  // Separate grammar into lexical and syntactic components 
  auto extract_result = extract_tokens(intern_result.first);
  error = get<2>(extract_result);
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  // Replace `Repeat` rules with pairs of recursive rules
  const SyntaxGrammar &syntax_grammar = expand_repeats(get<0>(extract_result));

  // Expand `String` and `Pattern` rules into full rule trees
  auto expand_tokens_result = expand_tokens(get<1>(extract_result));
  const LexicalGrammar &lex_grammar = expand_tokens_result.first;
  error = expand_tokens_result.second;
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  return make_tuple(syntax_grammar, lex_grammar, nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
