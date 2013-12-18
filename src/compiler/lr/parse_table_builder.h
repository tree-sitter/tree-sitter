#ifndef __TreeSitter__parse_table_builder__
#define __TreeSitter__parse_table_builder__

#include <unordered_map>
#include "grammar.h"
#include "item_set.h"
#include "parse_table.h"

namespace tree_sitter {
    namespace lr {
        class ParseTableBuilder {
            const Grammar grammar;
            ParseTable table;
            std::unordered_map<const ItemSet, size_t> state_indices;

            long state_index_for_item_set(const ItemSet &item_set) const;
            void add_shift_actions(const ItemSet &item_set, size_t state_index);
            void add_reduce_actions(const ItemSet &item_set, size_t state_index);
            size_t add_item_set(const ItemSet &item_set);
        public:
            ParseTableBuilder(const Grammar &grammar);
            static ParseTable build_table(const Grammar &grammar);
            void build();
        };
    }
}

#endif
