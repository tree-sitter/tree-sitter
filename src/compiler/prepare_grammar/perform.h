#ifndef __tree_sitter__prepare_grammar__
#define __tree_sitter__prepare_grammar__

#include <utility>

namespace tree_sitter {
    class Grammar;
    
    namespace prepare_grammar {
        std::pair<Grammar, Grammar> perform(const Grammar &);
    }
}

#endif
