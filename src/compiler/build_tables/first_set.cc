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
        class FirstSet : public rules::RuleFn<set<ISymbol>> {
            const PreparedGrammar *grammar;
            set<ISymbol> visited_symbols;
        public:
            explicit FirstSet(const PreparedGrammar *grammar) : grammar(grammar) {}

            set<ISymbol> apply_to(const ISymbol *rule) {
                auto insertion_result = visited_symbols.insert(*rule);
                if (insertion_result.second) {
                    return (rule->is_token()) ?
                        set<ISymbol>({ *rule }) :
                        apply(grammar->rule(*rule));
                } else {
                    return set<ISymbol>();
                }
            }

            set<ISymbol> apply_to(const rules::Metadata *rule) {
                return apply(rule->rule);
            }

            set<ISymbol> apply_to(const rules::Choice *rule) {
                set<ISymbol> result;
                for (const auto &el : rule->elements) {
                    auto &&next_syms = apply(el);
                    result.insert(next_syms.begin(), next_syms.end());
                }
                return result;
            }

            set<ISymbol> apply_to(const rules::Seq *rule) {
                auto &&result = apply(rule->left);
                if (rule_can_be_blank(rule->left, *grammar)) {
                    auto &&right_symbols = apply(rule->right);
                    result.insert(right_symbols.begin(), right_symbols.end());
                }
                return result;
            }
        };

        set<ISymbol> first_set(const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            return FirstSet(&grammar).apply(rule);
        }

        set<ISymbol> first_set(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            set<ISymbol> result;
            for (auto &item : item_set) {
                auto &&rule_set = first_set(item.rule, grammar);
                result.insert(rule_set.begin(), rule_set.end());
                if (rule_can_be_blank(item.rule, grammar))
                    result.insert(item.lookahead_sym);
            }
            return result;
        }
    }
}