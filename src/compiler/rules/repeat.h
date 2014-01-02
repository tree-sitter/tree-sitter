#ifndef __tree_sitter__repeat__
#define __tree_sitter__repeat__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Repeat : public Rule {
        public:
            Repeat(rule_ptr content);

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            const rule_ptr content;
        };
    }
}

#endif
