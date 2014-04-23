#include "compiler/build_tables/follow_sets.h"
#include "compiler/build_tables/first_set.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using std::map;
    using rules::ISymbol;
    using rules::rule_ptr;

    namespace build_tables {
        map<ISymbol, set<ISymbol>> follow_sets(const ParseItem &item,
                                             const PreparedGrammar &grammar) {
            map<ISymbol, set<ISymbol>> result;

            for (auto &pair : sym_transitions(item.rule)) {
                ISymbol symbol = pair.first;
                rule_ptr next_rule = pair.second;
                if (!symbol.is_token() && !symbol.is_built_in()) {
                    set<ISymbol> following_terminals = first_set(next_rule, grammar);
                    if (rule_can_be_blank(next_rule, grammar))
                        following_terminals.insert(item.lookahead_sym);
                    result.insert({ symbol, following_terminals });
                }
            }

            return result;
        }
    }
}
