#ifndef __tree_sitter__seq__
#define __tree_sitter__seq__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Seq : public Rule {
        public:
            Seq(rule_ptr left, rule_ptr right);
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            void accept(RuleVisitor &visitor) const;

            const rule_ptr left;
            const rule_ptr right;
        };
        
        rule_ptr seq(const std::initializer_list<rule_ptr> &rules);
    }
}

#endif
