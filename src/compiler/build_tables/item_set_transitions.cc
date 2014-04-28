#include "compiler/build_tables/item_set_transitions.h"
#include <unordered_set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    using std::map;
    using std::unordered_set;
    using rules::CharacterSet;
    using rules::ISymbol;

    namespace build_tables {
        template<typename T>
        static unordered_set<T> merge_sets(const unordered_set<T> &left, const unordered_set<T> &right) {
            unordered_set<T> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }

        const ISymbol placeholder = ISymbol(-99);

        static map<ISymbol, ParseItemSet> sym_transitions_for_rule(SymTransitions *self, const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            auto pair = self->transitions_cache.find(rule);
            if (pair != self->transitions_cache.end()) return pair->second;
            map<ISymbol, ParseItemSet> result;
            for (auto &transition : sym_transitions(rule)) {
                ParseItem new_item(placeholder, transition.second, 10, placeholder);
                result.insert({
                    transition.first,
                    item_set_closure(new_item, grammar)
                });
            }
            self->transitions_cache.insert({ rule, result });
            return result;
        }

        static map<ISymbol, ParseItemSet> sym_transitions_for_item(SymTransitions *self, const ParseItem &item, const PreparedGrammar &grammar) {
            auto result = sym_transitions_for_rule(self, item.rule, grammar);
            for (auto &pair : result) {
                ParseItemSet new_items;
                for (auto &i : pair.second) {
                    ParseItem new_item(i);
                    if (new_item.consumed_symbol_count > 0)
                        new_item.consumed_symbol_count = item.consumed_symbol_count + 1;
                    if (new_item.lookahead_sym == placeholder)
                        new_item.lookahead_sym = item.lookahead_sym;
                    if (new_item.lhs == placeholder)
                        new_item.lhs = item.lhs;
                    new_items.insert(new_item);
                }
                pair.second = new_items;
            }
            return result;
        }

        map<ISymbol, ParseItemSet>
        SymTransitions::operator()(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            map<ISymbol, ParseItemSet> result;
            for (const ParseItem &item : item_set)
                merge_sym_transitions<ParseItemSet>(result,
                                                    sym_transitions_for_item(this, item, grammar),
                                                    [&](const ParseItemSet &l, const ParseItemSet &r) {
                                                        return merge_sets(l, r);
                                                    });
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
                merge_char_transitions<LexItemSet>(result, item_transitions, [](const LexItemSet &l, const LexItemSet &r) {
                    return merge_sets(l, r);
                });
            }
            return result;
        }
    }
}