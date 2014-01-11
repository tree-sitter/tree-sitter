#ifndef __tree_sitter__search_for_symbols__
#define __tree_sitter__search_for_symbols__

#include "rules.h"

namespace tree_sitter {
    namespace prepare_grammar {
        bool search_for_symbols(const rules::rule_ptr &);
    }
}

#endif
