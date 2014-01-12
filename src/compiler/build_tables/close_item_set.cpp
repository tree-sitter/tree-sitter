#include "close_item_set.h"
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
        
        static vector<Item> closure_in_grammar(const Item &item, const Grammar &grammar) {
            vector<Item> result;
            add_item(result, item, grammar);
            return result;
        }

        ItemSet close_item_set(const ItemSet &item_set, const Grammar &grammar) {
            return ItemSet(closure_in_grammar(*item_set.begin(), grammar));
        }
    }
}