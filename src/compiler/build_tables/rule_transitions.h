#ifndef __tree_sitter__transitions__
#define __tree_sitter__transitions__

#include "character_set.h"
#include "symbol.h"
#include <map>

namespace tree_sitter  {
    namespace build_tables {
        std::map<rules::CharacterSet, rules::rule_ptr> char_transitions(const rules::rule_ptr &rule);
        std::map<rules::Symbol, rules::rule_ptr> sym_transitions(const rules::rule_ptr &rule);
    }
}

#endif