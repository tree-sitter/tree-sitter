#ifndef __tree_sitter__follow_sets__
#define __tree_sitter__follow_sets__

#include "item.h"
#include "symbol.h"
#include <set>
#include <unordered_map>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::unordered_map<rules::Symbol, std::set<rules::Symbol>> follow_sets(const ParseItem &item, const Grammar &grammar);
    }
}

#endif
