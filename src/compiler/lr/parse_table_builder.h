#ifndef __TreeSitter__parse_table_builder__
#define __TreeSitter__parse_table_builder__

#include <unordered_map>
#include "grammar.h"
#include "item_set.h"
#include "parse_table.h"

namespace tree_sitter {
    namespace lr {
        class ItemSet;

        struct ItemSetPointerHasher {
            std::size_t operator()(const std::shared_ptr<const ItemSet> &item_set) const {
                return std::hash<ItemSet>()(*item_set);
            }
        };
        
        class ParseTableBuilder {
            const Grammar grammar;
            ParseTable table;
            std::unordered_map<size_t, size_t> state_indices;

            size_t add_item_set(const std::shared_ptr<const ItemSet> item_set);
            long state_index_for_item_set(const ItemSet &item_set) const;
        public:
            ParseTableBuilder(const Grammar &grammar);
            static ParseTable build_table(const Grammar &grammar);
            void build();
        };
    }
}

#endif
