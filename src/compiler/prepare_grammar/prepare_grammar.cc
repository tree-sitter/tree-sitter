#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/prepare_grammar/intern_symbols.h"

namespace tree_sitter {
    using std::pair;

    namespace prepare_grammar {
        pair<PreparedGrammar, PreparedGrammar> prepare_grammar(const Grammar &input_grammar) {
            auto interned = intern_symbols(input_grammar);
            if (interned.second) {
                printf("Error! %s", interned.second->message().c_str());
                exit(1);
            }
            auto grammars = extract_tokens(interned.first);
            const auto &rule_grammar = expand_repeats(grammars.first);
            const auto &lex_grammar = grammars.second;
            return { rule_grammar, lex_grammar };
        }
    }
}
