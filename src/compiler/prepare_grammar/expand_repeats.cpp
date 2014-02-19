#include "expand_repeats.h"
#include "prepared_grammar.h"
#include "rules/visitor.h"
#include "rules/seq.h"
#include "rules/symbol.h"
#include "rules/choice.h"
#include "rules/blank.h"
#include "rules/repeat.h"
#include <map>

namespace tree_sitter {
    using std::string;
    using std::to_string;
    using std::map;
    using std::make_shared;
    using namespace rules;

    namespace prepare_grammar {
        class RepeatExpander : rules::Visitor {
        public:
            rule_ptr value;
            map<const string, const rule_ptr> aux_rules;
            
            rule_ptr apply(const rule_ptr &rule) {
                rule->accept(*this);
                return value;
            }
            
            rule_ptr make_repeat_helper(string name, const rule_ptr &rule) {
                return Choice::Build({
                    Seq::Build({ rule, make_shared<Symbol>(name, SymbolTypeAuxiliary) }),
                    make_shared<Blank>() });
            }
            
            void visit(const Repeat *rule) {
                rule_ptr inner_rule = apply(rule->content);
                string helper_rule_name = string("repeat_helper") + to_string(aux_rules.size() + 1);
                aux_rules.insert({ helper_rule_name, make_repeat_helper(helper_rule_name, inner_rule) });
                value = make_shared<Symbol>(helper_rule_name, SymbolTypeAuxiliary);
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
        };
        
        PreparedGrammar expand_repeats(const PreparedGrammar &grammar) {
            map<const string, const rule_ptr> rules;
            map<const string, const rule_ptr> aux_rules(grammar.aux_rules);
            RepeatExpander visitor;

            for (auto pair : grammar.rules)
                rules.insert({ pair.first, visitor.apply(pair.second) });
            
            aux_rules.insert(visitor.aux_rules.begin(), visitor.aux_rules.end());

            return PreparedGrammar(grammar.start_rule_name, rules, aux_rules);
        }
    }
}