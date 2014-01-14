#ifndef __tree_sitter__close_item_set__
#define __tree_sitter__close_item_set__

#include "item.h"

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        const ItemSet item_set_closure(const ItemSet &item_set, const Grammar &grammar);
    }
}

#endif
