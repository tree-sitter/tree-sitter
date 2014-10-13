#include "compiler/build_tables/get_metadata.h"
#include "compiler/build_tables/item.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/metadata.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

Item::Item(const rules::Symbol &lhs, const rules::rule_ptr rule)
    : lhs(lhs), rule(rule) {}

bool Item::is_done() const { return rule_can_be_blank(rule); }

int Item::precedence() const { return get_metadata(rule, rules::PRECEDENCE); }

}  // namespace build_tables
}  // namespace tree_sitter
