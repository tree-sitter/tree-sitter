#include "follow_sets.h"
#include "first_set.h"
#include "rule_transitions.h"
#include "rule_can_be_blank.h"
#include "prepared_grammar.h"

namespace tree_sitter {
    using std::set;
    using std::map;
    using rules::Symbol;
    using rules::rule_ptr;

    namespace build_tables {
        map<Symbol, set<Symbol>> follow_sets(const ParseItem &item, const PreparedGrammar &grammar) {
            map<Symbol, set<Symbol>> result;

            for (auto &pair : sym_transitions(item.rule)) {
                Symbol symbol = pair.first;
                rule_ptr next_rule = pair.second;
                if (grammar.has_definition(symbol)) {
                    set<Symbol> following_terminals = first_set(next_rule, grammar);
                    if (rule_can_be_blank(next_rule, grammar))
                        following_terminals.insert(item.lookahead_sym);
                    result.insert({ symbol, following_terminals });
                }
            }
            
            return result;
        }
    }
}
