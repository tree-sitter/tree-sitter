#ifndef COMPILER_BUILD_TABLES_ITEM_H_
#define COMPILER_BUILD_TABLES_ITEM_H_

#include "compiler/rules/symbol.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

class Item {
 public:
  Item(const rules::Symbol &lhs, rules::rule_ptr rule);

  rules::Symbol lhs;
  rules::rule_ptr rule;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_ITEM_H_
