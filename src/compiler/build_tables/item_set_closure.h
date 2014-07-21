#ifndef COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
#define COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_

#include <set>
#include "compiler/rules/symbol.h"
#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {
class SyntaxGrammar;

namespace build_tables {
const ParseItemSet item_set_closure(
    const ParseItem &item, const std::set<rules::Symbol> &lookahead_symbols,
    const SyntaxGrammar &grammar);
}
}

#endif  // COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
