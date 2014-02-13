#include "rules.h"
#include "rule_transitions.h"
#include "rule_can_be_blank.h"
#include "merge_transitions.h"

namespace tree_sitter {
    using std::map;
    using namespace rules;

    namespace build_tables {
        bool is_blank(const rule_ptr &rule) {
            return typeid(*rule) == typeid(Blank);
        }
        
        template<typename T>
        map<T, rule_ptr> merge_transitions(const map<T, rule_ptr> &left, const map<T, rule_ptr> &right);
        
        template<>
        map<CharacterSet, rule_ptr> merge_transitions(const map<CharacterSet, rule_ptr> &left, const map<CharacterSet, rule_ptr> &right) {
            auto transitions = merge_char_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) -> rule_ptr {
                return choice({ left, right });
            });
            return *static_cast<map<CharacterSet, rule_ptr> *>(&transitions);
        }

        template<>
        map<Symbol, rule_ptr> merge_transitions(const map<Symbol, rule_ptr> &left, const map<Symbol, rule_ptr> &right) {
            auto transitions = merge_sym_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) -> rule_ptr {
                return choice({ left, right });
            });
            return *static_cast<map<Symbol, rule_ptr> *>(&transitions);
        }
        
        template<typename T>
        map<T, rule_ptr> map_transitions(const map<T, rule_ptr> &initial, std::function<const rule_ptr(rule_ptr)> map_fn) {
            map<T, rule_ptr> result;
            for (auto &pair : initial)
                result.insert({ pair.first, map_fn(pair.second) });
            return result;
        }

        template<typename T>
        class TransitionsVisitor : public rules::Visitor {
        public:
            map<T, rule_ptr> value;
            
            static map<T, rule_ptr> transitions(const rule_ptr rule) {
                TransitionsVisitor<T> visitor;
                rule->accept(visitor);
                return visitor.value;
            }
            
            void visit_atom(const Rule *rule) {
                auto atom = dynamic_cast<const T *>(rule);
                if (atom) {
                    value = map<T, rule_ptr>();
                    value.insert({ *atom, blank() });
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
                value = map_transitions(transitions(rule->left), [&](const rule_ptr left_rule) -> rule_ptr {
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
                value = map_transitions(transitions(rule->content), [&](const rule_ptr &value) -> rule_ptr {
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
        
        map<CharacterSet, rule_ptr> char_transitions(const rule_ptr &rule) {
            return TransitionsVisitor<CharacterSet>::transitions(rule);
        }

        map<Symbol, rule_ptr> sym_transitions(const rule_ptr &rule) {
            return TransitionsVisitor<Symbol>::transitions(rule);
        }
    }
}
