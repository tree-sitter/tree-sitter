#include "item_set_closure.h"
#include "./next_symbols.h"
#include "grammar.h"
#include "item.h"
#include <vector>

using std::vector;

namespace tree_sitter {
    namespace build_tables {
        static bool contains(ItemSet items, Item item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        static void add_item(ItemSet &item_set, const Item &item, const Grammar &grammar) {
            if (!contains(item_set, item)) {
                item_set.insert(item);
                for (rules::Symbol rule : next_non_terminals(item, grammar)) {
                    Item next_item = Item::at_beginning_of_rule(rule.name, grammar);
                    add_item(item_set, next_item, grammar);
                }
            }
        }
        
        const ItemSet item_set_closure(const ItemSet &item_set, const Grammar &grammar) {
            ItemSet result;
            for (Item item : item_set)
                add_item(result, item, grammar);
            return result;
        }
    }
}