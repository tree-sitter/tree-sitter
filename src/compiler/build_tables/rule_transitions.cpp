#include "rule_transitions.h"
#include "rules.h"

using namespace tree_sitter::rules;

namespace tree_sitter {
    namespace build_tables {
        bool is_blank(const rule_ptr &rule) {
            return typeid(*rule) == typeid(Blank);
        }
        
        class TransitionsVisitor : public rules::Visitor {
        public:
            transition_map<Rule, Rule> value;

            void visit(const CharacterSet *rule) {
                value = transition_map<Rule, Rule>({{ rule->copy(), blank() }});
            }
            
            void visit(const Symbol *rule) {
                value = transition_map<Rule, Rule>({{ rule->copy(), blank() }});
            }

            void visit(const Choice *rule) {
                value = rule_transitions(rule->left);
                value.merge(rule_transitions(rule->right), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                    return choice({ left, right });
                });
            }

            void visit(const Seq *rule) {
                value = rule_transitions(rule->left).map<Rule>([&](const rule_ptr left_rule) -> rule_ptr {
                    if (is_blank(left_rule))
                        return rule->right;
                    else
                        return seq({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left)) {
                    value.merge(rule_transitions(rule->right), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                        return choice({ left, right });
                    });
                }
            }
            
            void visit(const Repeat *rule) {
                value = rule_transitions(rule->content).map<Rule>([&](const rule_ptr &value) -> rule_ptr {
                    return seq({ value, choice({ rule->copy(), blank() }) });
                });
            }
            
            void visit(const String *rule) {
                rule_ptr result = character(rule->value[0]);
                for (int i = 1; i < rule->value.length(); i++)
                    result = seq({ result, character(rule->value[i]) });
                value = rule_transitions(result);
            }
            
            void visit(const Pattern *rule) {
                value = rule_transitions(rule->to_rule_tree());
            }
        };
        
        transition_map<Rule, Rule> rule_transitions(const rule_ptr &rule) {
            TransitionsVisitor visitor;
            rule->accept(visitor);
            return visitor.value;
        }
        
        class EpsilonVisitor : public rules::Visitor {
        public:
            bool value;
            
            void default_visit(const Rule *) {
                value = false;
            }
            
            void visit(const Blank *) {
                value = true;
            }
            
            void visit(const Choice *rule) {
                value = rule_can_be_blank(rule->left) || rule_can_be_blank(rule->right);
            }
            
            void visit(const Seq *rule) {
                value = rule_can_be_blank(rule->left) && rule_can_be_blank(rule->right);
            }
            
            void visit(const Repeat *rule) {
                value = rule_can_be_blank(rule->content);
            }
        };
        
        bool rule_can_be_blank(const rule_ptr &rule) {
            EpsilonVisitor visitor;
            rule->accept(visitor);
            return visitor.value;
        }
    }
}
