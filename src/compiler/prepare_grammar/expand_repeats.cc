#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include <utility>
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
        class ExpandRepeats : public rules::IdentityRuleFn {
            string rule_name;

            rule_ptr apply_to(const Repeat *rule) {
                rule_ptr inner_rule = apply(rule->content);
                string helper_rule_name = rule_name + string("_repeat") + to_string(aux_rules.size() + 1);
                rule_ptr repeat_symbol = make_shared<Symbol>(helper_rule_name, rules::SymbolTypeAuxiliary);
                aux_rules.push_back({
                    helper_rule_name,
                    Choice::Build({
                        Seq::Build({ inner_rule, repeat_symbol }),
                        make_shared<Blank>()
                    })
                });
                return repeat_symbol;
            }

        public:
            ExpandRepeats(string rule_name) : rule_name(rule_name) {}

            vector<pair<string, rules::rule_ptr>> aux_rules;
        };

        PreparedGrammar expand_repeats(const PreparedGrammar &grammar) {
            vector<pair<string, rules::rule_ptr>> rules, aux_rules(grammar.aux_rules);

            for (auto &pair : grammar.rules) {
                ExpandRepeats expander(pair.first);
                rules.push_back({ pair.first, expander.apply(pair.second) });
                aux_rules.insert(aux_rules.end(), expander.aux_rules.begin(), expander.aux_rules.end());
            }

            return PreparedGrammar(rules, aux_rules);
        }
    }
}