#ifndef __TreeSitter__item_set__
#define __TreeSitter__item_set__

#include "item.h"
#include "grammar.h"

namespace tree_sitter {
    namespace lr {
        class ItemSet {
        public:
            ItemSet(const std::vector<Item> &items);
            ItemSet(const std::initializer_list<Item> &items);

            typedef Item value_type;
            typedef std::vector<Item>::const_iterator const_iterator;
            const_iterator begin() const;
            const_iterator end() const;
            size_t size() const;

            ItemSet closure_in_grammar(Grammar &grammar) const;
            TransitionMap<ItemSet> transitions() const;

            const std::vector<Item> contents;
        };
        
        std::ostream& operator<<(std::ostream &stream, const ItemSet &item_set);
    }
}

#endif
