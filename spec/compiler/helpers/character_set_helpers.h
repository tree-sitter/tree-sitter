#ifndef __tree_sitter__character_set_helpers__
#define __tree_sitter__character_set_helpers__

#include "tree_sitter/compiler.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {
    namespace rules {
        rule_ptr character(const std::set<CharacterRange> &ranges);
        rule_ptr character(const std::set<CharacterRange> &ranges, bool sign);
    }
}

#endif
