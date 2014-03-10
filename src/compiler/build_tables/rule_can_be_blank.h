#ifndef COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
#define COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        bool rule_can_be_blank(const rules::rule_ptr &rule);
        bool rule_can_be_blank(const rules::rule_ptr &rule, const PreparedGrammar &grammar);
    }
}

#endif  // COMPILER_BUILD_TABLES_RULE_CAN_BE_BLANK_H_
