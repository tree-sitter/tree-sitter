#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace prepare_grammar {
        PreparedGrammar expand_repeats(const PreparedGrammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_REPEATS_H_
