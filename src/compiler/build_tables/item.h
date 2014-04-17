#ifndef COMPILER_BUILD_TABLES_ITEM_H_
#define COMPILER_BUILD_TABLES_ITEM_H_

#include <unordered_set>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    namespace build_tables {
        class Item {
        public:
            Item(const rules::Symbol &lhs, rules::rule_ptr rule);
            bool is_done() const;

            rules::Symbol lhs;
            rules::rule_ptr rule;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_ITEM_H_
