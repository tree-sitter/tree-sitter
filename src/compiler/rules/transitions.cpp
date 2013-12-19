#include "transitions.h"
#include "rules.h"

namespace tree_sitter {
    namespace rules {
        class TransitionsVisitor : public RuleVisitor {
        public:
            TransitionMap<Rule> value;

            void visit(const Blank *rule) {
                value = TransitionMap<Rule>();
            }

            void visit(const CharClass *rule) {
                value = TransitionMap<Rule>({{ char_class(rule->value), blank() }});
            }
            
            void visit(const Char *rule) {
                value = TransitionMap<Rule>({{ character(rule->value), blank() }});
            }
            
            void visit(const Symbol *rule) {
                value = TransitionMap<Rule>({{ sym(rule->name), blank() }});
            }
            
            void visit(const Choice *rule) {
                value = transitions(rule->left);
                value.merge(transitions(rule->right), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                    return choice({ left, right });
                });
            }

            void visit(const Seq *rule) {
                value = transitions(rule->left).map<Rule>([&](rule_ptr left_rule) -> rule_ptr {
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
        
        TransitionMap<Rule> transitions(const rule_ptr &rule) {
            TransitionsVisitor visitor;
            rule->accept(visitor);
            return visitor.value;
        }
    }
}
