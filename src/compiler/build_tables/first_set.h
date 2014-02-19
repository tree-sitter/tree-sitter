#ifndef __tree_sitter__first_set__
#define __tree_sitter__first_set__

#include "rules/symbol.h"
#include <set>

namespace tree_sitter {
    class PreparedGrammar;
    
    namespace build_tables {
        std::set<rules::Symbol> first_set(const rules::rule_ptr &rule, const PreparedGrammar &grammar);
    }
}

#endif
