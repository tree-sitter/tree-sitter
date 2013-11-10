#ifndef __tree_sitter_pattern_h_
#define __tree_sitter_pattern_h_

#include "rule.h"

namespace tree_sitter {
    namespace rules {
        class Pattern : public Rule {
        public:
            Pattern(const char *string);
            Pattern(const std::string &string);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            std::string value;
        };
    }
}

#endif

