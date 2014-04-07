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

            void visit(const rules::Choice *rule) {
                value = apply(rule->left) || apply(rule->right);
            }

            void visit(const rules::Repeat *rule) {
                value = apply(rule->content);
            }

            void visit(const rules::Seq *rule) {
                int result = apply(rule->left);
                if (rule_can_be_blank(rule->left) && result == 0)
                    result = apply(rule->right);
                value = result;
            }

            void visit(const rules::Metadata *rule) {
                auto pair = rule->value.find(metadata_key);
                if (pair != rule->value.end())
                    value = pair->second;
            }
        };

        int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key) {
            return GetMetadata(key).apply(rule);
        }
    }
}