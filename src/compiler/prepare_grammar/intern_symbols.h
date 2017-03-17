#ifndef COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
#define COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_

#include <utility>
#include <string>
#include "compiler/compile_error.h"
#include "compiler/prepare_grammar/interned_grammar.h"

namespace tree_sitter {

struct InputGrammar;

namespace prepare_grammar {

std::pair<InternedGrammar, CompileError> intern_symbols(const InputGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
