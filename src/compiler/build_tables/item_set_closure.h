#ifndef COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
#define COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_

#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        const ParseItemSet item_set_closure(const ParseItemSet &item_set,
                                            const PreparedGrammar &grammar);
    }
}

#endif  // COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
