#ifndef __TreeSitter__item_set__
#define __TreeSitter__item_set__

#include "item.h"
#include "rule.h"
#include <vector>
#include <set>

namespace tree_sitter {
    namespace build_tables {
        class ItemSet;

        class ItemSet {
            const std::vector<Item> contents;
        public:
            ItemSet(const std::vector<Item> &items);
            bool operator==(const ItemSet &other) const;

            typedef Item value_type;
            typedef std::vector<Item>::const_iterator const_iterator;
            const_iterator begin() const;
            const_iterator end() const;
            size_t size() const;
        };
        
        std::ostream& operator<<(std::ostream &stream, const ItemSet &item_set);
    }
}

namespace std {
    template<>
    struct hash<const tree_sitter::build_tables::ItemSet> {
        size_t operator()(const tree_sitter::build_tables::ItemSet &item_set) const {
            size_t result = hash<size_t>()(item_set.size());
            for (auto item : item_set)
                result ^= hash<tree_sitter::build_tables::Item>()(item);
            return result;
        }
    };
}

#endif
