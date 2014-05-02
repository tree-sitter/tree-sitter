#ifndef COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
#define COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_

#include <utility>
#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class Grammar;
    class PreparedGrammar;

    namespace prepare_grammar {
        std::pair<PreparedGrammar, const GrammarError *> intern_symbols(const Grammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
