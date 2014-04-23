#ifndef COMPILER_BUILD_TABLES_ITEM_H_
#define COMPILER_BUILD_TABLES_ITEM_H_

#include <unordered_set>
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    namespace build_tables {
        class Item {
        public:
            Item(const rules::ISymbol &lhs, rules::rule_ptr rule);
            bool is_done() const;

            rules::ISymbol lhs;
            rules::rule_ptr rule;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_ITEM_H_
