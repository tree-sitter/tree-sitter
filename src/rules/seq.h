#ifndef __tree_sitter__seq__
#define __tree_sitter__seq__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Seq : public Rule {
        public:
            Seq(rule_ptr left, rule_ptr right);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            rule_ptr left;
            rule_ptr right;
        };
    }
}

#endif
