#include "compiler/build_tables/item_set_closure.h"
#include <algorithm>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/follow_sets.h"
#include "compiler/build_tables/item.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using rules::ISymbol;

    namespace build_tables {
        static bool contains(const ParseItemSet *items, const ParseItem &item) {
            if (items->empty()) return false;
            return (std::find(items->begin(), items->end(), item) != items->end());
        }

        static void add_item(ParseItemSet *item_set,
                             const ParseItem &item,
                             const PreparedGrammar &grammar) {
            if (!contains(item_set, item)) {
                item_set->insert(item);
                for (const auto &pair : follow_sets(item, grammar)) {
                    const ISymbol &non_terminal = pair.first;
                    const set<ISymbol> &terminals = pair.second;
                    for (const auto &terminal : terminals) {
                        ParseItem next_item(non_terminal, grammar.rule(non_terminal), 0, terminal);
                        add_item(item_set, next_item, grammar);
                    }
                }
            }
        }

        const ParseItemSet item_set_closure(const ParseItemSet &item_set,
                                            const PreparedGrammar &grammar) {
            ParseItemSet result;
            for (const ParseItem &item : item_set)
                add_item(&result, item, grammar);
            return result;
        }
    }
}