#ifndef __tree_sitter__prepare_grammar__
#define __tree_sitter__prepare_grammar__

#include "grammar.h"

namespace tree_sitter {
    namespace prepare_grammar {
        std::pair<Grammar, Grammar> perform(const Grammar &);
    }
}

#endif
