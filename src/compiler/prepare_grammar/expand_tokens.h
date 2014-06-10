#ifndef COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_

#include <utility>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace prepare_grammar {
        std::pair<PreparedGrammar, const GrammarError *>
        expand_tokens(const PreparedGrammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_EXPAND_TOKENS_H_

