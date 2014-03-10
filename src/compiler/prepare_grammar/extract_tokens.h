#ifndef __tree_sitter__extract_tokens__
#define __tree_sitter__extract_tokens__

#include <utility>

namespace tree_sitter {
    class PreparedGrammar;

    namespace prepare_grammar {
        std::pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &);
    }
}

#endif
