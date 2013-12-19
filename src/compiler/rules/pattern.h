#ifndef __tree_sitter_pattern_h_
#define __tree_sitter_pattern_h_

#include "rule.h"

namespace tree_sitter {
    namespace rules {
        class Pattern : public Rule {
            const std::string value;
        public:
            Pattern(const std::string &string);
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            void accept(RuleVisitor &visitor) const;
            rule_ptr to_rule_tree() const;
        };

        typedef std::shared_ptr<const Pattern> pattern_ptr;
        pattern_ptr pattern(const std::string &value);
    }
}

#endif

