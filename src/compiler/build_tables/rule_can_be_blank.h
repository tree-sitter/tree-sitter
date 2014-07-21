#ifndef COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
#define COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {

class SyntaxGrammar;

namespace build_tables {

bool rule_can_be_blank(const rules::rule_ptr &rule);
bool rule_can_be_blank(const rules::rule_ptr &rule,
                       const SyntaxGrammar &grammar);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
