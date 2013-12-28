#ifndef __TreeSitter__char_match__
#define __TreeSitter__char_match__

#include <unordered_map>
#include <string>

namespace tree_sitter {
    typedef enum {
        CharMatchTypeSpecific,
        CharMatchTypeClass,
        CharMatchTypeRange,
    } CharMatchType;
    
    typedef enum {
        CharClassWord,
        CharClassDigit
    } CharClass;
    
    struct CharMatch {
        CharMatchType type;
        union {
            CharClass character_class;
            char character;
            struct {
                char min_character;
                char max_character;
            } range;
        } value;
    };
    
    CharMatch CharMatchSpecific(char);
    CharMatch CharMatchClass(CharClass);
    CharMatch CharMatchRange(char, char);
    std::string CharMatchToString(CharMatch);

    bool operator==(const CharMatch &, const CharMatch &);
    std::ostream& operator<<(std::ostream& stream, const CharMatch &rule);
}

namespace std {
    template<>
    struct hash<tree_sitter::CharMatch> {
        size_t operator()(const tree_sitter::CharMatch &match) const {
            return (
                hash<int>()(match.type) ^
                hash<char>()(match.value.range.min_character) ^
                hash<char>()(match.value.range.max_character));
        }
    };
}

#endif
