#include "compiler/generate_code/token_description.h"
#include "tree_sitter/compiler.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
    using std::string;

    namespace generate_code {
        class TokenDescription : public rules::RuleFn<string> {
            string apply_to(const rules::Pattern *rule) {
                return "/" + rule->value + "/";
            }

            string apply_to(const rules::String *rule) {
                return "'" + rule->value + "'";
            }

            string apply_to(const rules::Metadata *rule) {
                return apply(rule->rule);
            }
        };

        std::string token_description(const rules::rule_ptr &rule) {
            return TokenDescription().apply(rule);
        }
    }
}
