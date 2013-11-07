#ifndef __tree_sitter__sym__
#define __tree_sitter__sym__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Symbol : public Rule {
        public:
            Symbol(int id);
            TransitionMap<Rule> transitions() const;
            Symbol * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            int id;
        };
    }
}

#endif