#ifndef __tree_sitter__first_set__
#define __tree_sitter__first_set__

#include "item.h"
#include "symbol.h"
#include <set>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::set<rules::Symbol> first_set(const rules::rule_ptr &rule, const Grammar &grammar);
    }
}

#endif
