#ifndef COMPILER_RULES_METADATA_H_
#define COMPILER_RULES_METADATA_H_

#include <string>
#include "compiler/rules/rule.h"

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            NONE = 0,
            START_TOKEN = 1,
        } MetadataValue;

        class Metadata : public Rule {
        public:
            Metadata(rule_ptr rule, MetadataValue value);

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;

            const rule_ptr rule;
            const MetadataValue value;
        };
    }
}

#endif  // COMPILER_RULES_METADATA_H_
