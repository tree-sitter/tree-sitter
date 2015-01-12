#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace prepare_grammar {

class InitialSyntaxGrammar;

InitialSyntaxGrammar expand_repeats(const InitialSyntaxGrammar &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
