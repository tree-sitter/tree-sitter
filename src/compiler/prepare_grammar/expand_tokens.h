#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_

#include <utility>
#include "compiler/compile_error.h"

namespace tree_sitter {

struct LexicalGrammar;

namespace prepare_grammar {

std::pair<LexicalGrammar, CompileError> expand_tokens(const LexicalGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
