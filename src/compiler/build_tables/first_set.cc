#include "compiler/build_tables/first_set.h"
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    using std::set;
    using rules::ISymbol;

    namespace build_tables {
        set<ISymbol> set_union(const set<ISymbol> &left, const set<ISymbol> &right) {
            set<ISymbol> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }

        class FirstSet : public rules::RuleFn<set<ISymbol>> {
            const PreparedGrammar *grammar;
            set<ISymbol> visited_symbols;
        public:
            explicit FirstSet(const PreparedGrammar *grammar) : grammar(grammar) {}

            set<ISymbol> apply_to(const ISymbol *rule) {
                if (visited_symbols.find(*rule) == visited_symbols.end()) {
                    visited_symbols.insert(*rule);

                    if (rule->is_token()) {
                        return set<ISymbol>({ *rule });
                    } else {
                        return apply(grammar->rule(*rule));
                    }
                } else {
                    return set<ISymbol>();
                }
            }

            set<ISymbol> apply_to(const rules::Metadata *rule) {
                return apply(rule->rule);
            }

            set<ISymbol> apply_to(const rules::Choice *rule) {
                return set_union(apply(rule->left), apply(rule->right));
            }

            set<ISymbol> apply_to(const rules::Seq *rule) {
                auto result = apply(rule->left);
                if (rule_can_be_blank(rule->left, *grammar)) {
                    return set_union(result, apply(rule->right));
                } else {
                    return result;
                }
            }
        };

        set<ISymbol> first_set(const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            return FirstSet(&grammar).apply(rule);
        }

        set<ISymbol> first_set(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            set<ISymbol> result;
            for (auto &item : item_set) {
                result = set_union(result, first_set(item.rule, grammar));
                if (rule_can_be_blank(item.rule, grammar))
                    result.insert(item.lookahead_sym);
            }
            return result;
        }
    }
}