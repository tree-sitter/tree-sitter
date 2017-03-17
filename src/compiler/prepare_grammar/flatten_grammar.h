#ifndef COMPILER_PREPARE_GRAMMAR_FLATTEN_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_FLATTEN_GRAMMAR_H_

#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/compile_error.h"
#include "compiler/grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

SyntaxVariable flatten_rule(const Variable &variable);
std::pair<SyntaxGrammar, CompileError> flatten_grammar(const InitialSyntaxGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_FLATTEN_GRAMMAR_H_
