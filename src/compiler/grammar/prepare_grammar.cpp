#include "prepare_grammar.h"
#include "extract_tokens.h"

using std::pair;

namespace tree_sitter {
    pair<Grammar, Grammar> prepare_grammar(const Grammar &input_grammar) {
        return extract_tokens(input_grammar);
    }
}
