#include "compiler/rules/character_range.h"
#include <algorithm>
#include <string>

namespace tree_sitter {
    using std::string;

    namespace rules {
        static const unsigned char MAX_CHAR = -1;

        CharacterRange::CharacterRange(unsigned char value) : min(value), max(value) {}
        CharacterRange::CharacterRange(unsigned char min, unsigned char max) : min(min),  max(max) {}

        bool CharacterRange::operator==(const CharacterRange &other) const {
            return min == other.min && max == other.max;
        }

        bool CharacterRange::operator<(const CharacterRange &other) const {
            if (min < other.min) return true;
            if (min > other.min) return false;
            if (max < other.max) return true;
            return false;
        }

        string escape_character(unsigned char input) {
            switch (input) {
                case '\0':
                    return "<EOF>";
                case MAX_CHAR:
                    return "<MAX>";
                default:
                    return string() + char(input);
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

