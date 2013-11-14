#include "item_set.h"

#include <iostream>

using namespace std;

namespace tree_sitter {
    namespace lr {
        ItemSet::ItemSet(const vector<Item> &items) : contents(items) {}
        ItemSet::ItemSet(const initializer_list<Item> &items) : contents(items) {}
        
        TransitionMap<ItemSet> ItemSet::transitions() const {
            return TransitionMap<ItemSet>();
        }
        
        bool vector_contains(vector<Item> items, lr::Item item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        void add_item(vector<Item> &vector, const Item &item, Grammar &grammar) {
            if (!vector_contains(vector, item)) {
                vector.push_back(item);
                for (rules::sym_ptr rule : item.next_symbols()) {
                    Item next_item = Item::at_beginning_of_rule(rule->name, grammar);
                    add_item(vector, next_item, grammar);
                }
            }
        }

        ItemSet ItemSet::closure_in_grammar(Grammar &grammar) const {
            vector<Item> items;
            for (Item item : *this)
                add_item(items, item, grammar);
            return ItemSet(items);
        }
        
#pragma mark - container
        ItemSet::const_iterator ItemSet::begin() const {
            return contents.begin();
        }

        ItemSet::const_iterator ItemSet::end() const {
            return contents.end();
        }

        size_t ItemSet::size() const {
            return contents.size();
        }
        
#pragma mark - printing
        ostream& operator<<(ostream &stream, const ItemSet &item_set) {
            stream << string("(item_set ");
            for (Item item : item_set) {
                stream << item;
                stream << string(" ");
            }
            stream << string(")");
            return stream;
        }
    }
}
