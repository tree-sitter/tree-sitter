#ifndef __tree_sitter__sym__
#define __tree_sitter__sym__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Symbol : public Rule {
        public:
            Symbol(const std::string &name);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            const std::string name;
        };
        
        typedef std::shared_ptr<const Symbol> sym_ptr;
        sym_ptr sym(const std::string &name);
    }
}

#endif