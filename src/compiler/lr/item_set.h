#ifndef __TreeSitter__item_set__
#define __TreeSitter__item_set__

#include "item.h"
#include "grammar.h"

namespace tree_sitter {
    namespace lr {
        class ItemSet;
        typedef std::shared_ptr<const ItemSet> item_set_ptr;

        class ItemSet {
            const std::vector<Item> contents;
        public:
            ItemSet(const std::vector<Item> &items);
            ItemSet(const std::initializer_list<Item> &items);
            ItemSet(const Item &item, const Grammar &grammar);

            typedef Item value_type;
            typedef std::vector<Item>::const_iterator const_iterator;
            const_iterator begin() const;
            const_iterator end() const;
            size_t size() const;

            TransitionMap<ItemSet> sym_transitions(const Grammar &grammar) const;
            TransitionMap<ItemSet> char_transitions(const Grammar &grammar) const;

            bool operator==(const ItemSet &other) const;
        };
        
        typedef std::shared_ptr<const ItemSet> item_set_ptr;
        std::ostream& operator<<(std::ostream &stream, const ItemSet &item_set);
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::lr::ItemSet> {
        size_t operator()(const tree_sitter::lr::ItemSet &item_set) const {
            size_t result = hash<size_t>()(item_set.size());
            for (auto item : item_set)
                result ^= hash<tree_sitter::lr::Item>()(item);
            return result;
        }
    };
}

#endif
