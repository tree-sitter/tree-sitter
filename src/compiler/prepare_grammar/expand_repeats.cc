#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/repeat.h"

namespace tree_sitter {
    using std::string;
    using std::vector;
    using std::pair;
    using std::to_string;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::Blank;
    using rules::Choice;
    using rules::Repeat;
    using rules::Rule;
    using rules::Seq;
    using rules::Symbol;

    namespace prepare_grammar {
        class ExpandRepeats : public rules::RuleFn<rule_ptr> {
            rule_ptr make_repeat_helper(string name, const rule_ptr &rule) {
                return Choice::Build({
                    Seq::Build({ rule, make_shared<Symbol>(name, rules::SymbolTypeAuxiliary) }),
                    make_shared<Blank>() });
            }

            void visit(const Repeat *rule) {
                rule_ptr inner_rule = apply(rule->content);
                string helper_rule_name = string("repeat_helper") + to_string(aux_rules.size() + 1);
                aux_rules.push_back({ helper_rule_name, make_repeat_helper(helper_rule_name, inner_rule) });
                value = make_shared<Symbol>(helper_rule_name, rules::SymbolTypeAuxiliary);
            }

            void visit(const Seq *rule) {
                value = Seq::Build({ apply(rule->left), apply(rule->right) });
            }

            void visit(const Choice *rule) {
                value = Choice::Build({ apply(rule->left), apply(rule->right) });
            }

            void default_visit(const Rule *rule) {
                value = rule->copy();
            }

        public:
            vector<pair<string, const rules::rule_ptr>> aux_rules;
        };

        PreparedGrammar expand_repeats(const PreparedGrammar &grammar) {
            vector<pair<string, rules::rule_ptr>> rules, aux_rules(grammar.aux_rules);
            ExpandRepeats expander;

            for (auto &pair : grammar.rules)
                rules.push_back({ pair.first, expander.apply(pair.second) });

            aux_rules.insert(aux_rules.end(), expander.aux_rules.begin(), expander.aux_rules.end());

            return PreparedGrammar(rules, aux_rules);
        }
    }
}