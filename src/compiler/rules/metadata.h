#ifndef COMPILER_RULES_METADATA_H_
#define COMPILER_RULES_METADATA_H_

#include <string>
#include <map>
#include "compiler/rules/rule.h"

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            START_TOKEN,
            PRECEDENCE,
            IS_TOKEN,
            DESCRIPTION,
        } MetadataKey;

        class Metadata : public Rule {
        public:
            Metadata(rule_ptr rule, std::map<MetadataKey, int> value);

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;
            int value_for(MetadataKey key) const;

            const rule_ptr rule;
            const std::map<MetadataKey, int> value;
        };
    }
}

#endif  // COMPILER_RULES_METADATA_H_
