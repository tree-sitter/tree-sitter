#include "compiler/build_tables/get_metadata.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
    namespace build_tables {
        int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key) {
            class GetMetadata : public rules::RuleFn<int> {
                rules::MetadataKey metadata_key;

                int apply_to(const rules::Metadata *rule) {
                    return rule->value_for(metadata_key);
                }

            public:
                explicit GetMetadata(rules::MetadataKey key) : metadata_key(key) {}
            };

            return GetMetadata(key).apply(rule);
        }
    }
}
