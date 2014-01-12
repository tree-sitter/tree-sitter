#ifndef __tree_sitter__close_item_set__
#define __tree_sitter__close_item_set__

#include "item_set.h"

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        ItemSet close_item_set(const ItemSet &item_set, const Grammar &grammar);
    }
}

#endif
