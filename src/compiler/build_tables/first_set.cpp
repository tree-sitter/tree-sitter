#include "first_set.h"
#include "tree_sitter/compiler.h"
#include "prepared_grammar.h"
#include "rule_can_be_blank.h"
#include "rules/visitor.h"
#include "rules/seq.h"
#include "rules/choice.h"

namespace tree_sitter {
    using std::set;
    using namespace rules;

    namespace build_tables {
        set<Symbol> set_union(const set<Symbol> &left, const set<Symbol> &right) {
            set<Symbol> result = left;
            result.insert(right.begin(), right.end());
            return result;
        }

        class FirstSet : public RuleFn<set<Symbol>> {
            const PreparedGrammar grammar;
        public:
            FirstSet(const PreparedGrammar &grammar) : grammar(grammar) {}

            void visit(const Symbol *rule) {
                if (grammar.has_definition(*rule)) {
                    value = apply(grammar.rule(*rule));
                } else {
                    value = set<Symbol>({ *rule });
                }
            }

            void visit(const Choice *rule) {
                value = set_union(apply(rule->left), apply(rule->right));
            }

            void visit(const Seq *rule) {
                auto result = apply(rule->left);
                if (rule_can_be_blank(rule->left, grammar)) {
                    result = set_union(result, apply(rule->right));
                }
                value = result;
            }
        };

        set<Symbol> first_set(const rule_ptr &rule, const PreparedGrammar &grammar) {
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