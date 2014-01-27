#include "item_set_closure.h"
#include "./follow_sets.h"
#include "grammar.h"
#include "item.h"
#include <vector>

using std::set;
using std::vector;

namespace tree_sitter {
    namespace build_tables {
        static bool contains(ParseItemSet items, ParseItem item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        static void add_item(ParseItemSet &item_set, const ParseItem &item, const Grammar &grammar) {
            if (!contains(item_set, item)) {
                item_set.insert(item);
                for (auto pair : follow_sets(item, grammar)) {
                    auto non_terminal = pair.first;
                    auto terminals = pair.second;
                    for (rules::Symbol terminal : terminals) {
                        auto next_item = ParseItem(non_terminal, grammar.rule(non_terminal), 0, terminal);
                        add_item(item_set, next_item, grammar);
                    }
                }
            }
        }

        const ParseItemSet item_set_closure(const ParseItemSet &item_set, const Grammar &grammar) {
            ParseItemSet result;
            for (ParseItem item : item_set)
                add_item(result, item, grammar);
            return result;
        }
    }
}