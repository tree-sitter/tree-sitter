#ifndef COMPILER_RULES_PATTERN_H_
#define COMPILER_RULES_PATTERN_H_

#include "compiler/rules/rule.h"

namespace tree_sitter {
    namespace rules {
        class Pattern : public Rule {
            const std::string value;
        public:
            Pattern(const std::string &string);

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            rule_ptr to_rule_tree() const;
        };
    }
}

#endif  // COMPILER_RULES_PATTERN_H_

