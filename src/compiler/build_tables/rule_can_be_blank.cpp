#include "compiler/build_tables/rule_can_be_blank.h"
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"

namespace tree_sitter  {
    using namespace rules;

    namespace build_tables {
        class CanBeBlank : public RuleFn<bool> {
        protected:
            void default_visit(const Rule *) {
                value = false;
            }

            virtual void visit(const Blank *) {
                value = true;
            }

            virtual void visit(const Repeat *rule) {
                value = true;
            }

            virtual void visit(const Choice *rule) {
                value = apply(rule->left) || apply(rule->right);
            }

            virtual void visit(const Seq *rule) {
                value = apply(rule->left) && apply(rule->right);
            }
        };

        class CanBeBlankRecursive : public CanBeBlank {
            const PreparedGrammar grammar;
            using CanBeBlank::visit;

        public:
            CanBeBlankRecursive(const PreparedGrammar &grammar) : grammar(grammar) {}

            void visit(const Symbol *rule) {
                value = grammar.has_definition(*rule) && apply(grammar.rule(*rule));
            }
        };

        bool rule_can_be_blank(const rule_ptr &rule) {
            return CanBeBlank().apply(rule);
        }

        bool rule_can_be_blank(const rule_ptr &rule, const PreparedGrammar &grammar) {
            return CanBeBlankRecursive(grammar).apply(rule);
        }
    }
}
