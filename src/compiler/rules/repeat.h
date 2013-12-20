#ifndef __tree_sitter__repeat__
#define __tree_sitter__repeat__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Repeat : public Rule {
        public:
            Repeat(rule_ptr content);
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            void accept(RuleVisitor &visitor) const;

            const rule_ptr content;
        };
    }
}

#endif
