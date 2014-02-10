#include "rule_transitions.h"
#include "rules.h"
#include "merge_transitions.h"

using namespace tree_sitter::rules;

namespace tree_sitter {
    namespace build_tables {
        bool is_blank(const rule_ptr &rule) {
            return typeid(*rule) == typeid(Blank);
        }
        
        template<typename T>
        transition_map<T, Rule> merge_transitions(const transition_map<T, Rule> &left, const transition_map<T, Rule> &right);
        
        template<>
        transition_map<CharacterSet, Rule> merge_transitions(const transition_map<CharacterSet, Rule> &left, const transition_map<CharacterSet, Rule> &right) {
            return merge_char_transitions<Rule>(left, right, [](rule_ptr left, rule_ptr right) -> rule_ptr {
                return choice({ left, right });
            });
        }

        template<>
        transition_map<Symbol, Rule> merge_transitions(const transition_map<Symbol, Rule> &left, const transition_map<Symbol, Rule> &right) {
            return merge_sym_transitions<Rule>(left, right, [](rule_ptr left, rule_ptr right) -> rule_ptr {
                return choice({ left, right });
            });
        }

        template<typename T>
        class TransitionsVisitor : public rules::Visitor {
        public:
            transition_map<T, Rule> value;
            
            static transition_map<T, Rule> transitions(const rule_ptr rule) {
                TransitionsVisitor<T> visitor;
                rule->accept(visitor);
                return visitor.value;
            }
            
            void visit_atom(const Rule *rule) {
                auto atom = dynamic_cast<const T *>(rule);
                if (atom) {
                    value = transition_map<T, Rule>({{ std::make_shared<T>(*atom), blank() }});
                }
            }

            void visit(const CharacterSet *rule) {
                visit_atom(rule);
            }
            
            void visit(const Symbol *rule) {
                visit_atom(rule);
            }

            void visit(const Choice *rule) {
                value = transitions(rule->left);
                value = merge_transitions<T>(transitions(rule->left), transitions(rule->right));
            }

            void visit(const Seq *rule) {
                value = transitions(rule->left).template map<Rule>([&](const rule_ptr left_rule) -> rule_ptr {
                    if (is_blank(left_rule))
                        return rule->right;
                    else
                        return seq({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left)) {
                    value = merge_transitions<T>(value, transitions(rule->right));
                }
            }
            
            void visit(const Repeat *rule) {
                value = transitions(rule->content).template map<Rule>([&](const rule_ptr &value) -> rule_ptr {
                    return seq({ value, choice({ rule->copy(), blank() }) });
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
        
        transition_map<CharacterSet, Rule> char_transitions(const rule_ptr &rule) {
            return TransitionsVisitor<CharacterSet>::transitions(rule);
        }

        transition_map<Symbol, Rule> sym_transitions(const rule_ptr &rule) {
            return TransitionsVisitor<Symbol>::transitions(rule);
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
