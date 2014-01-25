#include "./perform.h"
#include "./extract_tokens.h"
#include "./expand_repeats.h"

using std::pair;

namespace tree_sitter {
    namespace prepare_grammar {
        pair<Grammar, Grammar> perform(const Grammar &input_grammar) {
            auto rule_grammar = expand_repeats(input_grammar);
            return prepare_grammar::extract_tokens(rule_grammar);
        }
    }
}
