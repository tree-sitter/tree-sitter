#include "check_metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/visitor.h"
#include "compiler/build_tables/rule_can_be_blank.h"

namespace tree_sitter {
    namespace build_tables {
        class HasMetadata : public rules::RuleFn<bool> {
            rules::MetadataValue metadata_value;
        public:
            HasMetadata(rules::MetadataValue value) : metadata_value(value) {}
            
            void visit(const rules::Choice *rule) {
                value = apply(rule->left) || apply(rule->right);
            }

            void visit(const rules::Repeat *rule) {
                value = apply(rule->content);
            }

            void visit(const rules::Seq *rule) {
                bool result = apply(rule->left);
                if (rule_can_be_blank(rule->left))
                    result = result || apply(rule->right);
                value = result;
            }
            
            void visit(const rules::Metadata *rule) {
                value = rule->value & metadata_value;
            }
        };
        
        bool check_metadata(const rules::rule_ptr &rule, rules::MetadataValue value) {
            return HasMetadata(value).apply(rule);
        }
    }
}