#ifndef __tree_sitter__choice__
#define __tree_sitter__choice__

#include "rule.h"

namespace tree_sitter {
    namespace rules {
        class Choice : public Rule {
        public:
            Choice(rule_ptr left, rule_ptr right);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            const rule_ptr left;
            const rule_ptr right;
        };
        
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules);
    }
}

#endif