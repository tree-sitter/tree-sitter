#ifndef __tree_sitter__item_set_transitions__
#define __tree_sitter__item_set_transitions__

#include "character_set.h"
#include "symbol.h"
#include "item.h"
#include <map>

namespace tree_sitter {
    namespace build_tables {
        std::map<rules::CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set, const Grammar &grammar);
        std::map<rules::Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const Grammar &grammar);
    }
}

#endif
