#include "compiler/build_tables/item_set_transitions.h"
#include <set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/symbol.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using rules::CharacterSet;
    using rules::Symbol;

    namespace build_tables {
        map<Symbol, ParseItemSet>
        sym_transitions(const ParseItemSet &item_set, const SyntaxGrammar &grammar) {
            map<Symbol, ParseItemSet> result;
            for (const auto &pair : item_set) {
                const ParseItem &item = pair.first;
                const set<Symbol> &lookahead_symbols = pair.second;
                for (auto &transition : sym_transitions(item.rule)) {
                    ParseItem new_item(item.lhs, transition.second, item.consumed_symbol_count + 1);
                    merge_sym_transition<ParseItemSet>(&result, { transition.first, item_set_closure(new_item, lookahead_symbols, grammar) },
                                                        [](ParseItemSet *left, const ParseItemSet *right) {
                                                            for (auto &pair : *right)
                                                                left->operator[](pair.first).insert(pair.second.begin(), pair.second.end());
                                                        });
                }
            }
            return result;
        }

        map<CharacterSet, LexItemSet>
        char_transitions(const LexItemSet &item_set) {
            map<CharacterSet, LexItemSet> result;
            for (const LexItem &item : item_set) {
                for (auto &transition : char_transitions(item.rule)) {
                    LexItem next_item(item.lhs, transition.second);
                    merge_char_transition<LexItemSet>(&result, { transition.first, LexItemSet({ next_item }) },
                                                       [](LexItemSet *left, const LexItemSet *right) {
                                                           left->insert(right->begin(), right->end());
                                                       });
                }
            }
            return result;
        }
    }
}
