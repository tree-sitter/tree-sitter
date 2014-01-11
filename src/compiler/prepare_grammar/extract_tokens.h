#ifndef __tree_sitter__extract_tokens__
#define __tree_sitter__extract_tokens__

#include "grammar.h"

namespace tree_sitter {
    namespace prepare_grammar {
        std::pair<Grammar, Grammar> extract_tokens(const Grammar &);
    }
}

#endif
