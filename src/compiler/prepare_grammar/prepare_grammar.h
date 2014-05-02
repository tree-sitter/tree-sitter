#ifndef COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_

#include <utility>

namespace tree_sitter {
    class Grammar;
    class GrammarError;
    class PreparedGrammar;

    namespace prepare_grammar {
        std::tuple<PreparedGrammar, PreparedGrammar, const GrammarError *>
        prepare_grammar(const Grammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
