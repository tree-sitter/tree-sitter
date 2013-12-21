#ifndef __tree_sitter__transitions__
#define __tree_sitter__transitions__

#include "rule.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        transition_map<Rule, Rule> transitions(const rule_ptr &rule);
    }
}

#endif