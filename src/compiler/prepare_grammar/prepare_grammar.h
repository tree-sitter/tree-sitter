#ifndef COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_

#include <utility>
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    class Grammar;
    class GrammarError;

    namespace prepare_grammar {
        std::tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *>
        prepare_grammar(const Grammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_PREPARE_GRAMMAR_H_
