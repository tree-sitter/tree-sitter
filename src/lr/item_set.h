#ifndef __TreeSitter__item_set__
#define __TreeSitter__item_set__

#include "item.h"
#include "grammar.h"

namespace tree_sitter {
    namespace lr {
        class ItemSet {
        public:
            ItemSet(const Item &item, const Grammar &grammar);
            TransitionMap<ItemSet> transitions() const;
        };
    }
}

#endif
