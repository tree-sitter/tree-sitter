#ifndef __tree_sitter__char_class__
#define __tree_sitter__char_class__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            CharClassTypeWord,
            CharClassTypeDigit
        } CharClassType;

        class CharClass : public Rule {
        public:
            CharClass(CharClassType type);
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            const CharClassType value;
        };
    }
}

#endif
