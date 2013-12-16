#ifndef __tree_sitter__repeat__
#define __tree_sitter__repeat__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Repeat : public Rule {
        public:
            Repeat(rule_ptr content);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            const rule_ptr content;
        };
        
        rule_ptr repeat(const rule_ptr content);
    }
}

#endif
