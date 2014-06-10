#include "compiler/prepare_grammar/expand_tokens.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/string.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/character_set.h"
#include "compiler/prepare_grammar/parse_regex.h"

namespace tree_sitter {
    using std::string;
    using std::vector;
    using std::pair;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::String;
    using rules::Pattern;

    namespace prepare_grammar {
        class ExpandTokens : public rules::IdentityRuleFn {
            using rules::IdentityRuleFn::apply_to;

            rule_ptr apply_to(const String *rule) {
                vector<rule_ptr> elements;
                for (char val : rule->value)
                    elements.push_back(rules::CharacterSet({ val }).copy());
                return rules::Seq::Build(elements);
            }

            rule_ptr apply_to(const Pattern *rule) {
                auto pair = parse_regex(rule->value);
                if (!error)
                    error = pair.second;
                return pair.first;
            }

        public:
            const GrammarError *error;
            ExpandTokens() : error(nullptr) {}
        };

        pair<PreparedGrammar, const GrammarError *>
        expand_tokens(const PreparedGrammar &grammar) {
            vector<pair<string, rule_ptr>> rules, aux_rules;
            ExpandTokens expander;

            for (auto &pair : grammar.rules()) {
                auto rule = expander.apply(pair.second);
                if (expander.error)
                    return { PreparedGrammar(), expander.error };
                rules.push_back({ pair.first, rule });
            }

            for (auto &pair : grammar.aux_rules) {
                auto rule = expander.apply(pair.second);
                if (expander.error)
                    return { PreparedGrammar(), expander.error };
                aux_rules.push_back({ pair.first, rule });
            }

            return { PreparedGrammar(rules, aux_rules, grammar.options), nullptr };
        }
    }
}
