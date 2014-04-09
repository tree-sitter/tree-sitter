#include "get_metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/visitor.h"
#include "compiler/build_tables/rule_can_be_blank.h"

namespace tree_sitter {
    namespace build_tables {
        class GetMetadata : public rules::RuleFn<int> {
            rules::MetadataKey metadata_key;
        public:
            GetMetadata(rules::MetadataKey key) :
                metadata_key(key) {}

            int apply_to(const rules::Choice *rule) {
                return apply(rule->left) || apply(rule->right);
            }

            int apply_to(const rules::Repeat *rule) {
                return apply(rule->content);
            }

            int apply_to(const rules::Seq *rule) {
                int result = apply(rule->left);
                if (rule_can_be_blank(rule->left) && result == 0)
                    result = apply(rule->right);
                return result;
            }

            int apply_to(const rules::Metadata *rule) {
                auto pair = rule->value.find(metadata_key);
                if (pair != rule->value.end())
                    return pair->second;
                else
                    return 0;
            }
        };

        int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key) {
            return GetMetadata(key).apply(rule);
        }
    }
}