#include "compiler/build_tables/item_set_closure.h"
#include <set>
#include <vector>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/build_tables/first_set.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/item.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using std::vector;
    using std::pair;
    using rules::Symbol;
    using rules::rule_ptr;

    namespace build_tables {
        const ParseItemSet item_set_closure(const ParseItem &starting_item,
                                            const set<Symbol> &starting_lookahead_symbols,
                                            const PreparedGrammar &grammar) {
            ParseItemSet result;

            vector<pair<ParseItem, set<Symbol>>> items_to_process = {{starting_item, starting_lookahead_symbols}};
            while (!items_to_process.empty()) {
                ParseItem item = items_to_process.back().first;
                set<Symbol> new_lookahead_symbols = items_to_process.back().second;
                items_to_process.pop_back();
                
                set<Symbol> &lookahead_symbols = result[item];
                size_t previous_size = lookahead_symbols.size();
                lookahead_symbols.insert(new_lookahead_symbols.begin(), new_lookahead_symbols.end());

                if (lookahead_symbols.size() == previous_size)
                    continue;
                
                for (const auto &pair : sym_transitions(item.rule)) {
                    const Symbol &symbol = pair.first;
                    const rule_ptr &next_rule = pair.second;
                    
                    if (symbol.is_token() || symbol.is_built_in())
                        continue;
                    
                    set<Symbol> next_lookahead_symbols = first_set(next_rule, grammar);
                    if (rule_can_be_blank(next_rule, grammar))
                        next_lookahead_symbols.insert(lookahead_symbols.begin(), lookahead_symbols.end());
                    
                    items_to_process.push_back({
                        ParseItem(symbol, grammar.rule(symbol), 0),
                        next_lookahead_symbols
                    });
                }
            }
            
            return result;
        }
    }
}
