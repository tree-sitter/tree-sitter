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
  auto result = intern_symbols(input_grammar);
  const Grammar &grammar = result.first;
  const GrammarError *error = result.second;
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  auto grammars = extract_tokens(grammar);
  const SyntaxGrammar &rule_grammar = expand_repeats(get<0>(grammars));
  error = get<2>(grammars);
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  auto expand_tokens_result = expand_tokens(get<1>(grammars));
  const LexicalGrammar &lex_grammar = expand_tokens_result.first;
  error = expand_tokens_result.second;
  if (error)
    return make_tuple(SyntaxGrammar(), LexicalGrammar(), error);

  return make_tuple(rule_grammar, lex_grammar, nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
