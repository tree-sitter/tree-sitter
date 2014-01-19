#ifndef __tree_sitter__transitions__
#define __tree_sitter__transitions__

#include "rule.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace build_tables {
        bool rule_can_be_blank(const rules::rule_ptr &rule);
        transition_map<rules::Rule, rules::Rule> rule_transitions(const rules::rule_ptr &rule);
    }
}

#endif