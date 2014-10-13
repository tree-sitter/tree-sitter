#ifndef COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
#define COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_

#include <set>
#include "compiler/build_tables/parse_item.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

class SyntaxGrammar;

namespace build_tables {

const ParseItemSet item_set_closure(const ParseItem &,
                                    const std::set<rules::Symbol> &,
                                    const SyntaxGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_ITEM_SET_CLOSURE_H_
