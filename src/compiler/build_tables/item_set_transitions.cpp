#include "item_set_transitions.h"
#include "item_set_closure.h"
#include "rule_transitions.h"
#include "merge_transitions.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using rules::CharacterSet;
    using rules::Symbol;
    
    namespace build_tables {
        map<CharacterSet, LexItemSet> char_transitions(const LexItem &item) {
            map<CharacterSet, LexItemSet> result;
            for (auto &transition : char_transitions(item.rule)) {
                LexItem next_item(item.lhs, transition.second);
                result.insert({ transition.first, LexItemSet({ next_item }) });
            }
            return result;
        }
            
        map<Symbol, ParseItemSet> sym_transitions(const ParseItem &item, const Grammar &grammar) {
            map<Symbol, ParseItemSet> result;
            for (auto transition : sym_transitions(item.rule)) {
                Symbol rule = transition.first;
                auto consumed_symbols = item.consumed_symbols;
                consumed_symbols.push_back(rule.is_hidden());
                ParseItem new_item(item.lhs, transition.second, consumed_symbols, item.lookahead_sym);
                result.insert({ rule, item_set_closure(ParseItemSet({ new_item }), grammar) });
            }
            return result;
        }
        
        template<typename T>
        static set<T> merge_sets(const set<T> &left, const set<T> &right) {
            set<T> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }
        
        map<CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set, const Grammar &grammar) {
            map<CharacterSet, LexItemSet> result;
            for (const LexItem &item : item_set) {
                map<CharacterSet, LexItemSet> item_transitions = char_transitions(item);
                result = merge_char_transitions<LexItemSet>(result, item_transitions, [](LexItemSet left, LexItemSet right) {
                    return merge_sets(left, right);
                });
            }
            return result;
        }

        map<Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const Grammar &grammar) {
            map<Symbol, ParseItemSet> result;
            for (const ParseItem &item : item_set) {
                map<Symbol, ParseItemSet> item_transitions = sym_transitions(item, grammar);
                result = merge_sym_transitions<ParseItemSet>(result, item_transitions, [&](ParseItemSet left, ParseItemSet right) {
                    return merge_sets(left, right);
                });
            }
            return result;
        }
    }
}