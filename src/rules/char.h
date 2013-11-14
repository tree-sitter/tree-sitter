#ifndef __tree_sitter__char__
#define __tree_sitter__char__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class Char : public Rule {
        public:
            Char(char value);
            TransitionMap<Rule> transitions() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            const char value;
        };

        typedef std::shared_ptr<const Char> char_ptr;
        char_ptr character(char value);
    }
}

#endif
