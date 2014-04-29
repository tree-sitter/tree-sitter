#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/follow_sets.h"
#include "compiler/build_tables/item.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using rules::Symbol;
    using std::vector;

    namespace build_tables {
        const ParseItemSet item_set_closure(const ParseItem &item,
                                            const PreparedGrammar &grammar) {
            ParseItemSet result;
            vector<ParseItem> items_to_add = { item };
            while (!items_to_add.empty()) {
                ParseItem item = items_to_add.back();
                items_to_add.pop_back();
                auto insertion_result = result.insert(item);
                if (insertion_result.second) {
                    for (const auto &pair : follow_sets(item, grammar)) {
                        const Symbol &non_terminal = pair.first;
                        const set<Symbol> &terminals = pair.second;
                        for (const auto &terminal : terminals) {
                            ParseItem next_item(non_terminal, grammar.rule(non_terminal), 0, terminal);
                            items_to_add.push_back(next_item);
                        }
                    }
                }
            }
            return result;
        }
    }
}
