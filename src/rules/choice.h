#ifndef __tree_sitter__choice__
#define __tree_sitter__choice__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Choice : public Rule {
        public:
            Choice(const Rule &left, const Rule &right);
            Choice(std::shared_ptr<const Rule> left, std::shared_ptr<const Rule> right);
            TransitionMap<Rule> transitions() const;
            Choice * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            rule_ptr left;
            rule_ptr right;
        };
    }
}

#endif