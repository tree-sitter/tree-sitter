#include "item_set.h"

namespace tree_sitter {
    namespace lr {
        ItemSet::ItemSet(const Item &item, const Grammar &grammar) {

        }
        
        TransitionMap<ItemSet> ItemSet::transitions() const {
            return TransitionMap<ItemSet>();
        }
    }
}