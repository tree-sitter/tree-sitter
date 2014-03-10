#include "compiler/build_tables/rule_can_be_blank.h"
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"

namespace tree_sitter  {
    namespace build_tables {
        class CanBeBlank : public rules::RuleFn<bool> {
        protected:
            void default_visit(const rules::Rule *) {
                value = false;
            }

            virtual void visit(const rules::Blank *) {
                value = true;
            }

            virtual void visit(const rules::Repeat *rule) {
                value = true;
            }

            virtual void visit(const rules::Choice *rule) {
                value = apply(rule->left) || apply(rule->right);
            }

            virtual void visit(const rules::Seq *rule) {
                value = apply(rule->left) && apply(rule->right);
            }
        };

        class CanBeBlankRecursive : public CanBeBlank {
            const PreparedGrammar grammar;
            using CanBeBlank::visit;

        public:
            explicit CanBeBlankRecursive(const PreparedGrammar &grammar) : grammar(grammar) {}

            void visit(const rules::Symbol *rule) {
                value = grammar.has_definition(*rule) && apply(grammar.rule(*rule));
            }
        };

        bool rule_can_be_blank(const rules::rule_ptr &rule) {
            return CanBeBlank().apply(rule);
        }

        bool rule_can_be_blank(const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            return CanBeBlankRecursive(grammar).apply(rule);
        }
    }
}
