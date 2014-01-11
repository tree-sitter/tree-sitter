#include "./perform.h"
#include "extract_tokens.h"

using std::pair;

namespace tree_sitter {
    namespace prepare_grammar {
        pair<Grammar, Grammar> perform(const Grammar &input_grammar) {
            return prepare_grammar::extract_tokens(input_grammar);
        }
    }
}
