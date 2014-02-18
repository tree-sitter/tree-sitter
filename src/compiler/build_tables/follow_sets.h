#ifndef __tree_sitter__follow_sets__
#define __tree_sitter__follow_sets__

#include "item.h"
#include "rules/symbol.h"
#include <set>
#include <map>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::map<rules::Symbol, std::set<rules::Symbol>> follow_sets(const ParseItem &item, const Grammar &grammar);
    }
}

#endif
