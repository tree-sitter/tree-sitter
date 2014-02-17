#ifndef __tree_sitter__extract_tokens__
#define __tree_sitter__extract_tokens__

#include <utility>

namespace tree_sitter {
    class Grammar;
    
    namespace prepare_grammar {
        std::pair<Grammar, Grammar> extract_tokens(const Grammar &);
    }
}

#endif
