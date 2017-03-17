#ifndef COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_

#include <tuple>
#include "compiler/grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/compile_error.h"

namespace tree_sitter {
namespace prepare_grammar {

std::tuple<SyntaxGrammar, LexicalGrammar, CompileError> prepare_grammar(const InputGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
