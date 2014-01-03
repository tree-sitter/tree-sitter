#ifndef __tree_sitter__prepare_grammar__
#define __tree_sitter__prepare_grammar__

#include "grammar.h"

namespace tree_sitter {
    std::pair<Grammar, Grammar> prepare_grammar(const Grammar &);
}

#endif
