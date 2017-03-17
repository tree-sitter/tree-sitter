#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_

#include <tuple>
#include "compiler/compile_error.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

std::tuple<InitialSyntaxGrammar, LexicalGrammar, CompileError> extract_tokens(
  const InternedGrammar &
);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
