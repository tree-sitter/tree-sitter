#ifndef __tree_sitter__token__
#define __tree_sitter__token__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Token : public Rule {
        public:
            Token(const std::string &name);
            
            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;
            
            const std::string name;
        };
    }
}

#endif
