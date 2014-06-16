#include "compiler/build_tables/item_set_transitions.h"
#include <set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using rules::CharacterSet;
    using rules::Symbol;

    namespace build_tables {
        map<Symbol, ParseItemSet>
        SymTransitions::operator()(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            map<Symbol, ParseItemSet> result;

            for (const auto &pair : item_set) {
                const ParseItem &item = pair.first;
                const set<Symbol> &lookahead_symbols = pair.second;
                map<Symbol, ParseItemSet> result_for_item;
                for (auto &transition : sym_transitions(item.rule)) {
                    ParseItem new_item(item.lhs, transition.second, item.consumed_symbol_count + 1);
                    result_for_item.insert({
                        transition.first,
                        item_set_closure(new_item, lookahead_symbols, grammar)
                    });
                }
                
                merge_sym_transitions<ParseItemSet>(&result, result_for_item,
                                                    [](ParseItemSet *left, const ParseItemSet *right) {
                                                        for (auto &pair : *right)
                                                            left->operator[](pair.first).insert(pair.second.begin(), pair.second.end());
                                                    });
            }
            
            return result;
        }

        map<CharacterSet, LexItemSet>
        char_transitions(const LexItemSet &item_set, const PreparedGrammar &grammar) {
            map<CharacterSet, LexItemSet> result;
            for (const LexItem &item : item_set) {
                map<CharacterSet, LexItemSet> item_transitions;
                for (auto &transition : char_transitions(item.rule)) {
                    LexItem next_item(item.lhs, transition.second);
                    item_transitions.insert({
                        transition.first,
                        LexItemSet({ next_item })
                    });
                }
                merge_char_transitions<LexItemSet>(&result, item_transitions,
                                                   [](LexItemSet *left, const LexItemSet *right) {
                                                       left->insert(right->begin(), right->end());
                                                   });
            }
            return result;
        }
    }
}
