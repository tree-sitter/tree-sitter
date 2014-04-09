#include "compiler/build_tables/first_set.h"
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"

namespace tree_sitter {
    using std::set;
    using rules::Symbol;

    namespace build_tables {
        set<Symbol> set_union(const set<Symbol> &left, const set<Symbol> &right) {
            set<Symbol> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }

        class FirstSet : public rules::RuleFn<set<Symbol>> {
            const PreparedGrammar grammar;
            set<Symbol> visited_symbols;
        public:
            explicit FirstSet(const PreparedGrammar &grammar) : grammar(grammar) {}

            set<Symbol> apply_to(const Symbol *rule) {
                if (visited_symbols.find(*rule) == visited_symbols.end()) {
                    visited_symbols.insert(*rule);

                    if (grammar.has_definition(*rule)) {
                        return apply(grammar.rule(*rule));
                    } else {
                        return set<Symbol>({ *rule });
                    }
                } else {
                    return set<Symbol>();
                }
            }

            set<Symbol> apply_to(const rules::Metadata *rule) {
                return apply(rule->rule);
            }

            set<Symbol> apply_to(const rules::Choice *rule) {
                return set_union(apply(rule->left), apply(rule->right));
            }

            set<Symbol> apply_to(const rules::Seq *rule) {
                auto result = apply(rule->left);
                if (rule_can_be_blank(rule->left, grammar)) {
                    return set_union(result, apply(rule->right));
                } else {
                    return result;
                }
            }
        };

        set<Symbol> first_set(const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            return FirstSet(grammar).apply(rule);
        }

        set<Symbol> first_set(const ParseItemSet &item_set, const PreparedGrammar &grammar) {
            set<Symbol> result;
            for (auto &item : item_set) {
                result = set_union(result, first_set(item.rule, grammar));
                if (rule_can_be_blank(item.rule, grammar))
                    result.insert(item.lookahead_sym);
            }
            return result;
        }
    }
}