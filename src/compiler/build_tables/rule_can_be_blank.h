#ifndef __tree_sitter__rule_can_be_blank__
#define __tree_sitter__rule_can_be_blank__

#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace build_tables {
        bool rule_can_be_blank(const rules::rule_ptr &rule);
        bool rule_can_be_blank(const rules::rule_ptr &rule, const Grammar &grammar);
    }
}

#endif
