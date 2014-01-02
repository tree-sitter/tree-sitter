#ifndef __tree_sitter__char__
#define __tree_sitter__char__

#include "rule.h"
#include "char_match.h"

namespace tree_sitter  {
    namespace rules {
        class Character : public Rule {
        public:
            Character(char character);
            Character(CharClass character_class);
            Character(char min_character, char max_character);
            
            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            const CharMatch value;
        };

        typedef std::shared_ptr<const Character> char_ptr;
    }
}

#endif
