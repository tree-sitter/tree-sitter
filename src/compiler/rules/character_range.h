#ifndef COMPILER_RULES_CHARACTER_RANGE_H_
#define COMPILER_RULES_CHARACTER_RANGE_H_

#include <map>
#include <string>

namespace tree_sitter {
    namespace rules {
        struct CharacterRange {
            unsigned char min;
            unsigned char max;

            // IMPLICIT_CONSTRUCTORS
            CharacterRange(unsigned char value);
            CharacterRange(unsigned char min, unsigned char max);

            bool operator==(const CharacterRange &other) const;
            bool operator<(const CharacterRange &others) const;
            std::string to_string() const;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterRange> {
        size_t operator()(const tree_sitter::rules::CharacterRange &range) const {
            return (hash<unsigned char>()(range.min) ^ hash<unsigned char>()(range.max));
        }
    };
}

#endif  // COMPILER_RULES_CHARACTER_RANGE_H_
