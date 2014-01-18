#include "item_set_closure.h"
#include "./next_symbols.h"
#include "grammar.h"
#include "item.h"
#include <vector>

using std::vector;

namespace tree_sitter {
    namespace build_tables {
        static bool contains(ParseItemSet items, ParseItem item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        ParseItem parse_item_at_beginning_of_rule(const rules::Symbol &symbol, const Grammar &grammar) {
            return ParseItem(symbol.name, grammar.rule(symbol.name), 0);
        }

        static void add_item(ParseItemSet &item_set, const ParseItem &item, const Grammar &grammar) {
            if (!contains(item_set, item)) {
                item_set.insert(item);
                for (rules::Symbol rule : next_non_terminals(item, grammar)) {
                    auto next_item = parse_item_at_beginning_of_rule(rule, grammar);
                    add_item(item_set, next_item, grammar);
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