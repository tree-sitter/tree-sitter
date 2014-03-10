#include "rule_transitions.h"
#include "rule_can_be_blank.h"
#include "merge_transitions.h"
#include "rules/blank.h"
#include "rules/choice.h"
#include "rules/seq.h"
#include "rules/string.h"
#include "rules/repeat.h"
#include "rules/pattern.h"
#include "rules/character_set.h"
#include "rules/visitor.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using std::make_shared;
    using namespace rules;

    namespace build_tables {
        template<typename T>
        map<T, rule_ptr> merge_transitions(const map<T, rule_ptr> &left, const map<T, rule_ptr> &right);

        template<>
        map<CharacterSet, rule_ptr> merge_transitions(const map<CharacterSet, rule_ptr> &left, const map<CharacterSet, rule_ptr> &right) {
            auto transitions = merge_char_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) {
                return make_shared<Choice>(left, right);
            });
            return *static_cast<map<CharacterSet, rule_ptr> *>(&transitions);
        }

        template<>
        map<Symbol, rule_ptr> merge_transitions(const map<Symbol, rule_ptr> &left, const map<Symbol, rule_ptr> &right) {
            auto transitions = merge_sym_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) {
                return make_shared<Choice>(left, right);
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
        class RuleTransitions : public RuleFn<map<T, rule_ptr>> {
            void visit_atom(const Rule *rule) {
                auto atom = dynamic_cast<const T *>(rule);
                if (atom)
                    this->value = map<T, rule_ptr>({{ *atom, make_shared<Blank>() }});
            }

            void visit(const CharacterSet *rule) {
                visit_atom(rule);
            }

            void visit(const Symbol *rule) {
                visit_atom(rule);
            }

            void visit(const Choice *rule) {
                this->value = merge_transitions<T>(this->apply(rule->left),
                                                   this->apply(rule->right));
            }

            void visit(const Seq *rule) {
                auto result = map_transitions(this->apply(rule->left), [&](const rule_ptr left_rule) {
                    return Seq::Build({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left))
                    result = merge_transitions<T>(result, this->apply(rule->right));
                this->value = result;
            }

            void visit(const Repeat *rule) {
                this->value = map_transitions(this->apply(rule->content), [&](const rule_ptr &value) {
                    return Seq::Build({ value, make_shared<Choice>(rule->copy(), make_shared<Blank>()) });
                });
            }

            void visit(const String *rule) {
                rule_ptr result = make_shared<Blank>();
                for (char val : rule->value)
                    result = Seq::Build({ result, make_shared<CharacterSet>(set<CharacterRange>({ val })) });
                this->value = this->apply(result);
            }

            void visit(const Pattern *rule) {
                this->value = this->apply(rule->to_rule_tree());
            }
        };

        map<CharacterSet, rule_ptr> char_transitions(const rule_ptr &rule) {
            return RuleTransitions<CharacterSet>().apply(rule);
        }

        map<Symbol, rule_ptr> sym_transitions(const rule_ptr &rule) {
            return RuleTransitions<Symbol>().apply(rule);
        }
    }
}
