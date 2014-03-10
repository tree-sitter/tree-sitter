#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_

#include <utility>

namespace tree_sitter {
    class PreparedGrammar;

    namespace prepare_grammar {
        std::pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_TOKENS_H_
