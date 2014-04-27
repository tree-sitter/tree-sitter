#include "compiler/build_tables/rule_can_be_blank.h"
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter  {
    using std::set;

    namespace build_tables {
        class CanBeBlank : public rules::RuleFn<bool> {
        protected:
            bool apply_to(const rules::Blank *) {
                return true;
            }

            bool apply_to(const rules::Repeat *rule) {
                return true;
            }

            bool apply_to(const rules::Choice *rule) {
                for (const auto &element : rule->elements)
                    if (apply(element)) return true;
                return false;
            }

            bool apply_to(const rules::Seq *rule) {
                return apply(rule->left) && apply(rule->right);
            }

            bool apply_to(const rules::Metadata *rule) {
                return apply(rule->rule);
            }
        };

        class CanBeBlankRecursive : public CanBeBlank {
            const PreparedGrammar *grammar;
            set<rules::ISymbol> visited_symbols;
            using CanBeBlank::visit;

        public:
            using CanBeBlank::apply_to;
            explicit CanBeBlankRecursive(const PreparedGrammar *grammar) : grammar(grammar) {}

            bool apply_to(const rules::ISymbol *rule) {
                if (visited_symbols.find(*rule) == visited_symbols.end()) {
                    visited_symbols.insert(*rule);
                    return !rule->is_token() && apply(grammar->rule(*rule));
                } else {
                    return false;
                }
            }
        };

        bool rule_can_be_blank(const rules::rule_ptr &rule) {
            return CanBeBlank().apply(rule);
        }

        bool rule_can_be_blank(const rules::rule_ptr &rule, const PreparedGrammar &grammar) {
            return CanBeBlankRecursive(&grammar).apply(rule);
        }
    }
}
