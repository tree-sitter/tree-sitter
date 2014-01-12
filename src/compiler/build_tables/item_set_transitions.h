#ifndef __tree_sitter__item_set_transitions__
#define __tree_sitter__item_set_transitions__

#include "character.h"
#include "symbol.h"
#include "transition_map.h"
#include "item_set.h"

namespace tree_sitter {
    namespace build_tables {
        transition_map<rules::Character, ItemSet> char_transitions(const ItemSet &item_set, const Grammar &grammar);
        transition_map<rules::Symbol, ItemSet> sym_transitions(const ItemSet &item_set, const Grammar &grammar);
    }
}

#endif
