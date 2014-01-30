#ifndef __tree_sitter__char__
#define __tree_sitter__char__

#include "rule.h"
#include <vector>
#include <unordered_set>

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            CharClassWord,
            CharClassDigit
        } CharacterClass;
        
        typedef enum {
            CharacterMatchTypeSpecific,
            CharacterMatchTypeClass,
            CharacterMatchTypeRange,
        } CharacterMatchType;
        
        struct CharacterMatch {
            CharacterMatchType type;
            union {
                CharacterClass character_class;
                char character;
                struct {
                    char min_character;
                    char max_character;
                } range;
            } value;
            
            CharacterMatch(char);
            CharacterMatch(std::pair<char, char>);
            CharacterMatch(CharacterClass);
            bool operator==(const CharacterMatch &) const;
            std::string to_string() const;
        };

        class Character : public Rule {
        public:
            Character(char character);
            Character(CharacterClass character_class);
            Character(char min_character, char max_character);
            Character(const std::vector<CharacterMatch> &matches, bool sign);
            
            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            std::vector<CharacterMatch> matches;
            bool sign;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterMatch> {
        size_t operator()(const tree_sitter::rules::CharacterMatch &match) const {
            auto type = match.type;
            auto result = hash<short int>()(type);
            switch (type) {
                case tree_sitter::rules::CharacterMatchTypeClass:
                    result ^= hash<short int>()(match.value.character_class);
                case tree_sitter::rules::CharacterMatchTypeRange:
                    result ^= hash<char>()(match.value.range.min_character);
                    result ^= hash<char>()(match.value.range.max_character);
                case tree_sitter::rules::CharacterMatchTypeSpecific:
                    result ^= hash<char>()(match.value.character);
            }
            return result;
        }
    };
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::Character> : hash<tree_sitter::rules::Rule> {};
}

#endif
