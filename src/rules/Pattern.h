#ifndef __tree_sitter_pattern_h_
#define __tree_sitter_pattern_h_

#include "rule.h"

namespace tree_sitter {
    namespace rules {
        class Pattern : public Rule {
        public:
            Pattern(const std::string &string);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            rule_ptr to_rule_tree() const;
        private:
            const std::string value;
        };

        typedef std::shared_ptr<const Pattern> pattern_ptr;
        pattern_ptr pattern(const std::string &value);
    }
}

#endif

