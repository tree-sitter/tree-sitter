#ifndef __tree_sitter__prepare_grammar__
#define __tree_sitter__prepare_grammar__

#include <utility>

namespace tree_sitter {
    class Grammar;
    class PreparedGrammar;

    namespace prepare_grammar {
        std::pair<PreparedGrammar, PreparedGrammar> prepare_grammar(const Grammar &);
    }
}

#endif
