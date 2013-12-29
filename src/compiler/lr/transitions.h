#ifndef __tree_sitter__transitions__
#define __tree_sitter__transitions__

#include "rule.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace lr {
        transition_map<rules::Rule, rules::Rule> transitions(const rules::rule_ptr &rule);
    }
}

#endif