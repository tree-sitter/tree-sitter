#include "compiler/build_tables/item.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace build_tables {
        Item::Item(const rules::ISymbol &lhs, const rules::rule_ptr rule) :
            lhs(lhs),
            rule(rule) {}

        bool Item::is_done() const {
            return rule_can_be_blank(rule);
        }
    }
}

