#include "compiler/build_tables/item_set_transitions.h"
#include <unordered_set>
#include <vector>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    using std::map;
    using std::vector;
    using std::unordered_set;
    using rules::CharacterSet;
    using rules::ISymbol;

    namespace build_tables {
        template<typename T>
        static unordered_set<T> merge_sets(unordered_set<T> &left, const unordered_set<T> &right) {
            left.insert(right.begin(), right.end());
            return left;
        }

        const ISymbol placeholder_lookahead = ISymbol(-100);
        const ISymbol placeholder_lhs = ISymbol(-101);

        static map<ISymbol, ParseItemSet> sym_transitions_for_rule(SymTransitions *self, const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            auto pair = self->transitions_cache.find(rule);
            if (pair != self->transitions_cache.end()) return pair->second;
            map<ISymbol, ParseItemSet> result;
            for (auto &transition : sym_transitions(rule)) {
                ParseItem new_item(placeholder_lhs, transition.second, 1, placeholder_lookahead);
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
                vector<ParseItem> new_items;
                auto &items = pair.second;
                for (auto iter = items.begin(), end = items.end(); iter != end;) {
                    ParseItem new_item(*iter);
                    bool changed = false;
                    if (new_item.consumed_symbol_count > 0) {
                        new_item.consumed_symbol_count = item.consumed_symbol_count + 1;
                        changed = true;
                    }
                    if (new_item.lookahead_sym == placeholder_lookahead) {
                        new_item.lookahead_sym = item.lookahead_sym;
                        changed = true;
                    }
                    if (new_item.lhs == placeholder_lhs) {
                        new_item.lhs = item.lhs;
                        changed = true;
                    }
                    if (changed) {
                        iter = pair.second.erase(iter);
                        new_items.push_back(new_item);
                    } else {
                        ++iter;
                    }
                }
                pair.second.insert(new_items.begin(), new_items.end());
            }
            return result;
        }

        map<ISymbol, ParseItemSet>
        SymTransitions::operator()(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            map<ISymbol, ParseItemSet> result;
            for (const ParseItem &item : item_set)
                merge_sym_transitions<ParseItemSet>(result,
                                                    sym_transitions_for_item(this, item, grammar),
                                                    [&](ParseItemSet &l, const ParseItemSet &r) {
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
                merge_char_transitions<LexItemSet>(result, item_transitions, [](LexItemSet &l, const LexItemSet &r) {
                    return merge_sets(l, r);
                });
            }
            return result;
        }
    }
}