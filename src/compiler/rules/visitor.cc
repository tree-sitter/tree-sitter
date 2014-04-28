#include "compiler/rules/visitor.h"
#include "compiler/rules/rule.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/repeat.h"

namespace tree_sitter {
    using std::vector;

    namespace rules {
        Visitor::~Visitor() {}

        rule_ptr IdentityRuleFn::default_apply(const Rule *rule) {
            return rule->copy();
        }

        rule_ptr IdentityRuleFn::apply_to(const Choice *rule) {
            vector<rule_ptr> rules;
            for (const auto &el : rule->elements)
                rules.push_back(apply(el));
            return Choice::Build(rules);
        }

        rule_ptr IdentityRuleFn::apply_to(const Seq *rule) {
            return Seq::Build({ apply(rule->left), apply(rule->right) });
        }

        rule_ptr IdentityRuleFn::apply_to(const Repeat *rule) {
            return std::make_shared<Repeat>(apply(rule->content));
        }

        rule_ptr IdentityRuleFn::apply_to(const Metadata *rule) {
            return std::make_shared<Metadata>(apply(rule->rule), rule->value);
        }
    }
}
