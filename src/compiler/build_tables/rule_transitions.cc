#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
    using std::map;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::Symbol;
    using rules::CharacterSet;

    namespace build_tables {
        template<typename T>
        void merge_transitions(map<T, rule_ptr> *left, const map<T, rule_ptr> &right);

        template<>
        void merge_transitions(map<CharacterSet, rule_ptr> *left, const map<CharacterSet, rule_ptr> &right) {
            merge_char_transitions<rule_ptr>(left, right, [](rule_ptr *left, const rule_ptr *right) {
                return rules::Choice::Build({ *left, *right });
            });
        }

        template<>
        void merge_transitions(map<Symbol, rule_ptr> *left, const map<Symbol, rule_ptr> &right) {
            merge_sym_transitions<rule_ptr>(left, right, [](rule_ptr *left, const rule_ptr *right) {
                return rules::Choice::Build({ *left, *right });
            });
        }

        template<typename T>
        void transform_transitions(map<T, rule_ptr> *transitions, std::function<const rule_ptr(rule_ptr)> fn) {
            for (auto &pair : *transitions)
                pair.second = fn(pair.second);
        }

        template<typename T>
        class RuleTransitions : public rules::RuleFn<map<T, rule_ptr>> {
            map<T, rule_ptr> apply_to_atom(const rules::Rule *rule) {
                auto atom = dynamic_cast<const T *>(rule);
                if (atom)
                    return map<T, rule_ptr>({{ *atom, make_shared<rules::Blank>() }});
                else
                    return map<T, rule_ptr>();
            }

            map<T, rule_ptr> apply_to(const CharacterSet *rule) {
                return apply_to_atom(rule);
            }

            map<T, rule_ptr> apply_to(const Symbol *rule) {
                return apply_to_atom(rule);
            }

            map<T, rule_ptr> apply_to(const rules::Choice *rule) {
                map<T, rule_ptr> result;
                for (const auto &el : rule->elements)
                    merge_transitions<T>(&result, this->apply(el));
                return result;
            }

            map<T, rule_ptr> apply_to(const rules::Seq *rule) {
                auto result = this->apply(rule->left);
                transform_transitions(&result, [&](const rule_ptr &left_rule) {
                    return rules::Seq::Build({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left)) {
                    merge_transitions<T>(&result, this->apply(rule->right));
                }
                return result;
            }

            map<T, rule_ptr> apply_to(const rules::Repeat *rule) {
                auto result = this->apply(rule->content);
                transform_transitions(&result, [&](const rule_ptr &value) {
                    return rules::Seq::Build({ value, rule->copy() });
                });
                return result;
            }

            map<T, rule_ptr> apply_to(const rules::Metadata *rule) {
                auto result = this->apply(rule->rule);
                transform_transitions(&result, [&](const rule_ptr &to_rule) {
                    return make_shared<rules::Metadata>(to_rule, rule->value);
                });
                return result;
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
