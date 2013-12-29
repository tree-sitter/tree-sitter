#include "transitions.h"
#include "rules.h"

using namespace tree_sitter::rules;

namespace tree_sitter {
    namespace lr {
        class TransitionsVisitor : public rules::Visitor {
        public:
            transition_map<Rule, Rule> value;

            void visit(const Blank *rule) {
                value = transition_map<Rule, Rule>();
            }

            void visit(const Character *rule) {
                value = transition_map<Rule, Rule>({{ std::make_shared<Character>(*rule), blank() }});
            }
            
            void visit(const Symbol *rule) {
                value = transition_map<Rule, Rule>({{ std::make_shared<Symbol>(*rule), blank() }});
            }
            
            void visit(const Choice *rule) {
                value = transitions(rule->left);
                value.merge(transitions(rule->right), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                    return choice({ left, right });
                });
            }

            void visit(const Seq *rule) {
                value = transitions(rule->left).map<Rule>([&](const rule_ptr left_rule) -> rule_ptr {
                    if (typeid(*left_rule) == typeid(Blank))
                        return rule->right;
                    else
                        return seq({ left_rule, rule->right });
                });
            }
            
            void visit(const Repeat *rule) {
                value = transitions(rule->content).map<Rule>([&](const rule_ptr &value) -> rule_ptr {
                    return seq({ value, choice({ repeat(rule->content), blank() }) });
                });
            }
            
            void visit(const String *rule) {
                rule_ptr result = character(rule->value[0]);
                for (int i = 1; i < rule->value.length(); i++)
                    result = seq({ result, character(rule->value[i]) });
                value = transitions(result);
            }
            
            void visit(const Pattern *rule) {
                value = transitions(rule->to_rule_tree());
            }
        };
        
        transition_map<Rule, Rule> transitions(const rule_ptr &rule) {
            TransitionsVisitor visitor;
            rule->accept(visitor);
            return visitor.value;
        }
    }
}
