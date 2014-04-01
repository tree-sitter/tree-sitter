#include "compiler/build_tables/rule_transitions.h"
#include <set>
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
    using std::map;
    using std::set;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::Symbol;
    using rules::CharacterSet;

    namespace build_tables {
        template<typename T>
        map<T, rule_ptr> merge_transitions(const map<T, rule_ptr> &left, const map<T, rule_ptr> &right);

        template<>
        map<CharacterSet, rule_ptr>
        merge_transitions(const map<CharacterSet, rule_ptr> &left, const map<CharacterSet, rule_ptr> &right) {
            return merge_char_transitions<rule_ptr>(left, right, [](rule_ptr left, rule_ptr right) {
                return make_shared<rules::Choice>(left, right);
            });
        }

        template<>
        map<Symbol, rule_ptr>
        merge_transitions(const map<Symbol, rule_ptr> &left, const map<Symbol, rule_ptr> &right) {
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
            void visit_atom(const rules::Rule *rule) {
                auto atom = dynamic_cast<const T *>(rule);
                if (atom)
                    this->value = map<T, rule_ptr>({{ *atom, make_shared<rules::Blank>() }});
            }

            void visit(const CharacterSet *rule) {
                visit_atom(rule);
            }

            void visit(const Symbol *rule) {
                visit_atom(rule);
            }

            void visit(const rules::Choice *rule) {
                this->value = merge_transitions<T>(this->apply(rule->left),
                                                   this->apply(rule->right));
            }

            void visit(const rules::Seq *rule) {
                auto result = map_transitions(this->apply(rule->left), [&](const rule_ptr left_rule) {
                    return rules::Seq::Build({ left_rule, rule->right });
                });
                if (rule_can_be_blank(rule->left))
                    result = merge_transitions<T>(result, this->apply(rule->right));
                this->value = result;
            }

            void visit(const rules::Repeat *rule) {
                this->value = map_transitions(this->apply(rule->content), [&](const rule_ptr &value) {
                    return rules::Seq::Build({
                        value,
                        make_shared<rules::Choice>(rule->copy(), make_shared<rules::Blank>())
                    });
                });
            }

            void visit(const rules::String *rule) {
                rule_ptr result = make_shared<rules::Blank>();
                for (char val : rule->value)
                    result = rules::Seq::Build({
                        result,
                        make_shared<CharacterSet>(set<rules::CharacterRange>({ val }))
                    });
                this->value = this->apply(result);
            }

            void visit(const rules::Pattern *rule) {
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
