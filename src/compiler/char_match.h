#ifndef __TreeSitter__char_match__
#define __TreeSitter__char_match__

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

#endif
