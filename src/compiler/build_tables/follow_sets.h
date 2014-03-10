#ifndef __tree_sitter__follow_sets__
#define __tree_sitter__follow_sets__

#include <set>
#include <map>
#include "compiler/build_tables/item.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {

        /*
         *  Returns a map of non-terminal symbols to sets of terminal symbols.
         *  The keys are the non-terminals which may appear first in the given
         *  item. The values are the sets of terminals which can appear immediately
         *  after the corresponding non-terminals.
         */
        std::map<rules::Symbol, std::set<rules::Symbol>> follow_sets(const ParseItem &item, const PreparedGrammar &grammar);

    }
}

#endif
