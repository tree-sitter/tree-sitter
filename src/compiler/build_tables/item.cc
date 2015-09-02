#include "compiler/build_tables/item.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

Item::Item(const rules::Symbol &lhs, const rules::rule_ptr rule)
    : lhs(lhs), rule(rule) {}

}  // namespace build_tables
}  // namespace tree_sitter
