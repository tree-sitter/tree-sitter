#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/follow_sets.h"
#include "compiler/build_tables/item.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using rules::Symbol;
    using std::vector;
    using std::pair;

    namespace build_tables {
        const ParseItemSet item_set_closure(const ParseItem &starting_item,
                                            const set<Symbol> &starting_lookahead_symbols,
                                            const PreparedGrammar &grammar) {
            ParseItemSet result;
            vector<pair<ParseItem, set<Symbol>>> pairs_to_add = { {starting_item, starting_lookahead_symbols} };
            while (!pairs_to_add.empty()) {
                auto pair = pairs_to_add.back();
                pairs_to_add.pop_back();
                auto &item = pair.first;
                auto &lookahead_symbols = pair.second;
                
                bool new_stuff_added = false;
                auto &existing_lookahead_symbols = result[item];
                for (auto &sym : lookahead_symbols) {
                    auto insertion_result = existing_lookahead_symbols.insert(sym);
                    if (insertion_result.second) new_stuff_added = true;
                }

                if (new_stuff_added) {
                    for (const auto &pair : follow_sets(item, lookahead_symbols, grammar)) {
                        const Symbol &non_terminal = pair.first;
                        const set<Symbol> &terminals = pair.second;
                        pairs_to_add.push_back({
                            ParseItem(non_terminal, grammar.rule(non_terminal), 0),
                            terminals
                        });
                    }
                }
            }
            
            return result;
        }
    }
}
