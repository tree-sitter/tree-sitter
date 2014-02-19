#ifndef __tree_sitter__expand_repeats__
#define __tree_sitter__expand_repeats__

#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class PreparedGrammar;
    
    namespace prepare_grammar {
        PreparedGrammar expand_repeats(const PreparedGrammar &);
    }
}

#endif
