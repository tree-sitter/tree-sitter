#ifndef __tree_sitter__string__
#define __tree_sitter__string__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class String : public Rule {
        public:
            String(std::string value);
            TransitionMap<Rule> transitions() const;
            String * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            std::string value;
        };
    }
}

#endif