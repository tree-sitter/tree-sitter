#ifndef __tree_sitter__first_terminal__
#define __tree_sitter__first_terminal__

#include "item_set.h"
#include "symbol.h"
#include <set>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::set<rules::Symbol> next_terminals(const rules::rule_ptr &rule, const Grammar &grammar);
        std::set<rules::Symbol> next_terminals(const ItemSet &item_set, const Grammar &grammar);
        std::set<rules::Symbol> next_terminals(const Item &item, const Grammar &grammar);
        std::set<rules::Symbol> next_non_terminals(const Item &item, const Grammar &grammar);
    }
}
#endif
