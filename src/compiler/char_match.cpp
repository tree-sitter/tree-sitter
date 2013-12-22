#include "char_match.h"

using std::string;

namespace tree_sitter {
    CharMatch CharMatchSpecific(char value) {
        CharMatch result = { .type = CharMatchTypeSpecific };
        result.value.character = value;
        return result;
    }
    
    CharMatch CharMatchClass(CharClass value) {
        CharMatch result = { .type = CharMatchTypeSpecific };
        result.value.character = value;
        return result;
    }
    
    CharMatch CharMatchRange(char min, char max) {
        CharMatch result = { .type = CharMatchTypeSpecific };
        result.value.range.min_character = min;
        result.value.range.max_character = max;
        return result;
    }
    
    string CharMatchToString(CharMatch match) {
        switch (match.type) {
            case CharMatchTypeClass:
                switch (match.value.character_class) {
                    case CharClassDigit:
                        return "<digit>";
                    case CharClassWord:
                        return "<word>";
                }
            case CharMatchTypeSpecific:
                return string("'") + string(&match.value.character) + "'";
            case CharMatchTypeRange:
                return (
                    string("'") +
                    string(&match.value.range.min_character) + "-" +
                    string(&match.value.range.max_character) + "'");
        }
    }
    
    bool operator==(const CharMatch &left, const CharMatch &right) {
        if (left.type != right.type)
            return false;
        switch (left.type) {
            case CharMatchTypeClass:
                return (left.value.character_class == right.value.character_class);
            case CharMatchTypeSpecific:
                return (left.value.character == right.value.character);
            case CharMatchTypeRange:
                return (
                    left.value.range.min_character == right.value.range.min_character &&
                    left.value.range.max_character == right.value.range.max_character);
        }
    }

    std::ostream& operator<<(std::ostream& stream, const CharMatch &match) {
        return stream << CharMatchToString(match);
    }
}