#ifndef __tree_sitter__character__
#define __tree_sitter__character__

#include "rule.h"
#include <unordered_set>

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            CharClassWord,
            CharClassDigit
        } CharacterClass;
        
        typedef enum {
            CharacterRangeTypeSpecific,
            CharacterRangeTypeClass,
            CharacterRangeTypeRange,
        } CharacterRangeType;
        
        struct CharacterRange {
            CharacterRangeType type;
            union {
                CharacterClass character_class;
                char character;
                struct {
                    char min_character;
                    char max_character;
                } range;
            } value;
            
            CharacterRange(char);
            CharacterRange(const std::pair<char, char>);
            CharacterRange(CharacterClass);
            bool operator==(const CharacterRange &) const;
            std::string to_string() const;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterRange> {
        size_t operator()(const tree_sitter::rules::CharacterRange &match) const {
            auto type = match.type;
            auto result = hash<short int>()(type);
            switch (type) {
                case tree_sitter::rules::CharacterRangeTypeClass:
                    result ^= hash<short int>()(match.value.character_class);
                case tree_sitter::rules::CharacterRangeTypeRange:
                    result ^= hash<char>()(match.value.range.min_character);
                    result ^= hash<char>()(match.value.range.max_character);
                case tree_sitter::rules::CharacterRangeTypeSpecific:
                    result ^= hash<char>()(match.value.character);
            }
            return result;
        }
    };
}

namespace tree_sitter  {
    namespace rules {

        class CharacterSet : public Rule {
        public:
            CharacterSet(char character);
            CharacterSet(CharacterClass character_class);
            CharacterSet(char min_character, char max_character);
            CharacterSet(const std::unordered_set<CharacterRange> &matches, bool sign);
            
            bool operator==(const Rule& other) const;
            bool operator==(const CharacterSet& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            std::unordered_set<CharacterRange> ranges;
            bool sign;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterSet> : hash<tree_sitter::rules::Rule> {};
}

#endif
