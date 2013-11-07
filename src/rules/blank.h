#ifndef __tree_sitter__blank__
#define __tree_sitter__blank__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Blank : public Rule {
        public:
            Blank();
            TransitionMap<Rule> transitions() const;
            Blank * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        };
    }
}

#endif