#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/prepared_grammar.h"
#include "compiler/prepare_grammar/extract_tokens.h"
#include "compiler/prepare_grammar/expand_repeats.h"
#include "compiler/prepare_grammar/expand_tokens.h"
#include "compiler/prepare_grammar/intern_symbols.h"

namespace tree_sitter {
    using std::tuple;
    using std::make_tuple;

    namespace prepare_grammar {
        tuple<PreparedGrammar, PreparedGrammar, const GrammarError *>
        prepare_grammar(const Grammar &input_grammar) {
            auto result = intern_symbols(input_grammar);
            const PreparedGrammar &grammar = result.first;
            const GrammarError *error = result.second;

            if (error)
                return make_tuple(PreparedGrammar(), PreparedGrammar(), error);

            auto grammars = extract_tokens(grammar);
            const PreparedGrammar &rule_grammar = expand_repeats(grammars.first);
            auto expand_tokens_result = expand_tokens(grammars.second);
            const PreparedGrammar &lex_grammar = expand_tokens_result.first;
            error = expand_tokens_result.second;
            
            if (error)
                return make_tuple(PreparedGrammar(), PreparedGrammar(), error);
            
            return make_tuple(rule_grammar, lex_grammar, nullptr);
        }
    }
}
