#ifndef COMPILER_BUILD_TABLES_FOLLOW_SETS_H_
#define COMPILER_BUILD_TABLES_FOLLOW_SETS_H_

#include <set>
#include <map>
#include "compiler/build_tables/parse_item.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {

        /*
         *  Returns a map of non-terminal symbols to sets of terminal symbols.
         *  The keys are the non-terminals which may appear first in the given
         *  item. The values are the sets of terminals which can appear immediately
         *  after the corresponding non-terminals.
         */
        std::map<rules::ISymbol, std::set<rules::ISymbol>>
        follow_sets(const ParseItem &item, const PreparedGrammar &grammar);

    }
}

#endif  // COMPILER_BUILD_TABLES_FOLLOW_SETS_H_
