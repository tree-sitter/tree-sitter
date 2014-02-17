#include "tree_sitter/compiler.h"

namespace tree_sitter {
    using std::string;
    
    namespace rules {
        static const char MAX_CHAR = '\xff';
        
        CharacterRange::CharacterRange(char value) : min(value), max(value) {}
        CharacterRange::CharacterRange(char min, char max) : min(min),  max(max) {}
        
        bool CharacterRange::operator==(const CharacterRange &other) const {
            return min == other.min && max == other.max;
        }
        
        bool CharacterRange::operator<(const CharacterRange &other) const {
            if (min < other.min) return true;
            if (min > other.min) return false;
            if (max < other.max) return true;
            return false;
        }
        
        string escape_character(char input) {
            switch (input) {
                case '\0':
                    return "<EOF>";
                case MAX_CHAR:
                    return "<MAX>";
                default:
                    return string() + input;
            }
        }
        
        string CharacterRange::to_string() const {
            if (min == 0 && max == MAX_CHAR)
                return "<ANY>";
            if (min == max)
                return escape_character(min);
            else
                return string() + escape_character(min) + "-" + escape_character(max);
        }
    }
}

