#include "item_set_closure.h"
#include "./next_symbols.h"
#include "grammar.h"
#include "item.h"
#include <vector>

using std::vector;

namespace tree_sitter {
    namespace build_tables {
        static bool vector_contains(vector<Item> items, build_tables::Item item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        static void add_item(vector<Item> &vector, const Item &item, const Grammar &grammar) {
            if (!vector_contains(vector, item)) {
                vector.push_back(item);
                for (rules::Symbol rule : next_non_terminals(item, grammar)) {
                    Item next_item = Item::at_beginning_of_rule(rule.name, grammar);
                    add_item(vector, next_item, grammar);
                }
            }
        }
        
        ItemSet item_set_closure(const ItemSet &item_set, const Grammar &grammar) {
            vector<Item> items;
            for (Item item : item_set)
                add_item(items, item, grammar);
            return ItemSet(items);
        }
    }
}