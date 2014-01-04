#ifndef __tree_sitter__non_terminal__
#define __tree_sitter__non_terminal__

#include "symbol.h"

namespace tree_sitter  {
    namespace rules {
        class NonTerminal : public Symbol {
        public:
            NonTerminal(const std::string &name);
            
            bool operator==(const Rule& other) const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;
        };
    }
}

#endif
