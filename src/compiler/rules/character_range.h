#ifndef __tree_sitter_character_range_h__
#define __tree_sitter_character_range_h__

#include <map>

namespace tree_sitter {
    namespace rules {
        struct CharacterRange {
            char min;
            char max;
            CharacterRange(char);
            CharacterRange(char, char);
            bool operator==(const CharacterRange &) const;
            bool operator<(const CharacterRange &) const;
            std::string to_string() const;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterRange> {
        size_t operator()(const tree_sitter::rules::CharacterRange &range) const {
            return (hash<char>()(range.min) ^ hash<char>()(range.max));
        }
    };
}

#endif
