#ifndef __tree_sitter__item_set_transitions__
#define __tree_sitter__item_set_transitions__

#include "character_set.h"
#include "symbol.h"
#include "transition_map.h"
#include "item.h"

namespace tree_sitter {
    namespace build_tables {
        transition_map<rules::CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set, const Grammar &grammar);
        transition_map<rules::Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const Grammar &grammar);
    }
}

#endif
