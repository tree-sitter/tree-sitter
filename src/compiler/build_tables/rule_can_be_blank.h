#ifndef COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
#define COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_

#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

bool rule_can_be_blank(const rules::Rule &rule);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
