#include "item_set_transitions.h"
#include "item_set_closure.h"
#include "rule_transitions.h"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace tree_sitter {
    using rules::CharacterSet;
    
    namespace build_tables {
        template<typename T>
        static std::set<T> merge_sets(const std::set<T> &left, const std::set<T> &right) {
            std::set<T> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }
            
        transition_map<CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set, const Grammar &grammar) {
            transition_map<CharacterSet, LexItemSet> result;
            for (LexItem item : item_set) {
                transition_map<CharacterSet, LexItemSet> item_transitions;
                for (auto transition : char_transitions(item.rule)) {
                    auto rule = transition.first;
                    auto new_item = LexItem(item.lhs, transition.second);
                    auto new_item_set = LexItemSet({ new_item });
                    item_transitions.add(rule, make_shared<LexItemSet>(new_item_set));
                }

                result.merge(item_transitions, [](shared_ptr<const LexItemSet> left, shared_ptr<const LexItemSet> right) -> shared_ptr<const LexItemSet> {
                    return make_shared<LexItemSet>(merge_sets(*left, *right));
                });
            }
            
            return result;
        }
        
        transition_map<rules::Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const Grammar &grammar) {
            transition_map<rules::Symbol, ParseItemSet> result;
            for (ParseItem item : item_set) {
                transition_map<rules::Symbol, ParseItemSet> item_transitions;
                for (auto transition : sym_transitions(item.rule)) {
                    auto rule = transition.first;
                    auto consumed_symbols = item.consumed_symbols;
                    consumed_symbols.push_back(rule->is_auxiliary);
                    auto new_item = ParseItem(item.lhs, transition.second, consumed_symbols, item.lookahead_sym);
                    auto new_item_set = item_set_closure(ParseItemSet({ new_item }), grammar);
                    item_transitions.add(rule, make_shared<ParseItemSet>(new_item_set));
                }

                result.merge(item_transitions, [](shared_ptr<const ParseItemSet> left, shared_ptr<const ParseItemSet> right) -> shared_ptr<const ParseItemSet> {
                    return make_shared<ParseItemSet>(merge_sets(*left, *right));
                });
            }
            
            return result;
        }
    }
}