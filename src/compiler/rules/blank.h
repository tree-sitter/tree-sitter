#ifndef __tree_sitter__blank__
#define __tree_sitter__blank__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Blank : public Rule {
        public:
            Blank();
            
            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;
        };
    }
}

#endif