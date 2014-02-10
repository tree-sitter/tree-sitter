#ifndef __tree_sitter__sym__
#define __tree_sitter__sym__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Symbol : public Rule {
        public:
            Symbol(const std::string &name);
            Symbol(const std::string &name, bool is_auxiliary);

            bool operator==(const Rule& other) const;
            bool operator==(const Symbol &other) const;
            
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;
            bool operator<(const Symbol &other) const;

            std::string name;
            bool is_auxiliary;
        };
        
        typedef std::shared_ptr<Symbol> sym_ptr;
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::Symbol> : hash<tree_sitter::rules::Rule> {};
}


#endif