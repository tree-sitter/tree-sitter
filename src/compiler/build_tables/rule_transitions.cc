#include "compiler/build_tables/rule_transitions.h"
#include <set>
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/interned_symbol.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::ISymbol;
    using rules::CharacterSet;
    using rules::Metadata;

    namespace build_tables {
        template<typename T>
        map<T, rule_ptr>
        merge_transitions(const map<T, rule_ptr> &left, const map<T, rule_ptr> &right);

        template<>
        map<CharacterSet, rule_ptr>
        merge_transitions(const map<CharacterSet, rule_ptr> &left, const map<CharacterSet, rule_ptr> &right) {
            return merge_char_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) {
                return make_shared<rules::Choice>(left, right);
            });
        }

        template<>
        map<ISymbol, rule_ptr>
        merge_transitions(const map<ISymbol, rule_ptr> &left, const map<ISymbol, rule_ptr> &right) {
            return merge_sym_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) {
                return make_shared<rules::Choice>(left, right);
            });
        }

        template<typename T>
        map<T, rule_ptr>
        map_transitions(const map<T, rule_ptr> &initial, std::function<const rule_ptr(rule_ptr)> map_fn) {
            map<T, rule_ptr> result;
            for (auto &pair : initial)
                result.insert({ pair.first, map_fn(pair.second) });
            return result;
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

            map<T, rule_ptr> apply_to(const ISymbol *rule) {
                return apply_to_atom(rule);
            }

            map<T, rule_ptr> apply_to(const rules::Choice *rule) {
                auto left_transitions = this->apply(rule->left);
                auto right_transitions = this->apply(rule->right);
                return merge_transitions<T>(left_transitions, right_transitions);
            }

            map<T, rule_ptr> apply_to(const rules::Seq *rule) {
                auto result = map_transitions(this->apply(rule->left), [&](const rule_ptr left_rule) {
                    return rules::Seq::Build({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left)) {
                    auto right_transitions = this->apply(rule->right);
                    result = merge_transitions<T>(result, right_transitions);
                }
                return result;
            }

            map<T, rule_ptr> apply_to(const rules::Repeat *rule) {
                return map_transitions(this->apply(rule->content), [&](const rule_ptr &value) {
                    return rules::Seq::Build({ value, rule->copy() });
                });
            }

            map<T, rule_ptr> apply_to(const rules::Metadata *rule) {
                return map_transitions(this->apply(rule->rule), [&](const rule_ptr &to_rule) {
                    return make_shared<Metadata>(to_rule, rule->value);
                });
            }

            map<T, rule_ptr> apply_to(const rules::String *rule) {
                rule_ptr result = make_shared<rules::Blank>();
                for (char val : rule->value)
                    result = rules::Seq::Build({
                        result,
                        make_shared<CharacterSet>(set<rules::CharacterRange>({ val }))
                    });
                return this->apply(result);
            }

            map<T, rule_ptr> apply_to(const rules::Pattern *rule) {
                return this->apply(rule->to_rule_tree());
            }
        };

        map<CharacterSet, rule_ptr> char_transitions(const rule_ptr &rule) {
            return RuleTransitions<CharacterSet>().apply(rule);
        }

        map<ISymbol, rule_ptr> sym_transitions(const rule_ptr &rule) {
            return RuleTransitions<ISymbol>().apply(rule);
        }
    }
}
