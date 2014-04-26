#ifndef COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
#define COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_

#include <utility>
#include <string>

namespace tree_sitter {
    class Grammar;
    class PreparedGrammar;

    class GrammarError {
        std::string rule_name;
    public:
        GrammarError(std::string rule_name);
        std::string message() const;
    };

    namespace prepare_grammar {
        std::pair<PreparedGrammar, const GrammarError *> intern_symbols(const Grammar &);
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_INTERN_SYMBOLS_H_
