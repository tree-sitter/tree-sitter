#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class SyntaxGrammar;

    namespace prepare_grammar {
        SyntaxGrammar expand_repeats(const SyntaxGrammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
