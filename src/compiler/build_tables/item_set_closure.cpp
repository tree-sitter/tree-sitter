#include "item_set_closure.h"
#include "tree_sitter/compiler.h"
#include "./follow_sets.h"
#include "item.h"
#include "prepared_grammar.h"
#include <algorithm>

namespace tree_sitter {
    using std::set;
    using rules::Symbol;

    namespace build_tables {
        static bool contains(const ParseItemSet &items, const ParseItem &item) {
            return items.size() > 0 && (std::find(items.begin(), items.end(), item) != items.end());
        }

        static void add_item(ParseItemSet &item_set, const ParseItem &item, const PreparedGrammar &grammar) {
            if (!contains(item_set, item)) {
                item_set.insert(item);
                for (auto &pair : follow_sets(item, grammar)) {
                    Symbol non_terminal = pair.first;
                    set<Symbol> terminals = pair.second;
                    for (auto &terminal : terminals) {
                        ParseItem next_item(non_terminal, grammar.rule(non_terminal), {}, terminal);
                        add_item(item_set, next_item, grammar);
                    }
                }
            }
        }

        const ParseItemSet item_set_closure(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            ParseItemSet result;
            for (ParseItem item : item_set)
                add_item(result, item, grammar);
            return result;
        }
    }
}