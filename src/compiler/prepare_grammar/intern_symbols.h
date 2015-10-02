#ifndef COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
#define COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_

#include <utility>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/interned_grammar.h"

namespace tree_sitter {
namespace prepare_grammar {

std::pair<InternedGrammar, const GrammarError *> intern_symbols(const Grammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
