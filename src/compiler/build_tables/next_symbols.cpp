#include "next_symbols.h"
#include "rule_transitions.h"
#include "grammar.h"
#include <vector>

using std::set;
using std::vector;
using std::dynamic_pointer_cast;

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        template<bool isNonTerminal>
        set<rules::Symbol> next_symbols(const Item &item, const Grammar &grammar) {
            set<rules::Symbol> result;
            for (auto pair : rule_transitions(item.rule)) {
                auto symbol = dynamic_pointer_cast<const rules::Symbol>(pair.first);
                if (symbol && (grammar.has_definition(*symbol) == isNonTerminal))
                    result.insert(*symbol);
            }
            return result;
        }
        
        set<rules::Symbol> next_terminals(const Item &item, const Grammar &grammar) {
            return next_symbols<false>(item, grammar);
        }

        set<rules::Symbol> next_non_terminals(const Item &item, const Grammar &grammar) {
            return next_symbols<true>(item, grammar);
        }

        set<rules::Symbol> next_terminals(const ItemSet &item_set, const Grammar &grammar) {
            set<rules::Symbol> result;
            for (Item item : item_set)
                for (rules::Symbol symbol : next_terminals(item, grammar))
                    result.insert(symbol);
            return result;
        }
    }
}