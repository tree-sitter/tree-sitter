#include "rules.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        CharacterRange::CharacterRange(char character) : type(CharacterRangeTypeSpecific) { value.character = character; }
        CharacterRange::CharacterRange(CharacterClass klass) : type(CharacterRangeTypeClass) { value.character_class = klass; }
        CharacterRange::CharacterRange(const std::pair<char, char> bounds) : type(CharacterRangeTypeRange) {
            value.range.min_character = bounds.first;
            value.range.max_character = bounds.second;
        }
        
        bool CharacterRange::operator==(const CharacterRange &right) const {
            if (type != right.type)
                return false;
            switch (type) {
                case CharacterRangeTypeClass:
                    return (value.character_class == right.value.character_class);
                case CharacterRangeTypeSpecific:
                    return (value.character == right.value.character);
                case CharacterRangeTypeRange:
                    return (value.range.min_character == right.value.range.min_character &&
                            value.range.max_character == right.value.range.max_character);
            }
        }
        
        string CharacterRange::to_string() const {
            switch (type) {
                case CharacterRangeTypeClass:
                    switch (value.character_class) {
                        case CharClassDigit:
                            return "<digit>";
                        case CharClassWord:
                            return "<word>";
                    }
                case CharacterRangeTypeSpecific:
                    return (value.character == '\0') ?
                        "<EOF>" :
                        string("'") + value.character + "'";
                case CharacterRangeTypeRange:
                    return (string("'") +
                            value.range.min_character + "'-'" +
                            value.range.max_character + "'");
            }
        }
        
        CharacterSet::CharacterSet(char character) : ranges({ CharacterRange(character) }), sign(true) {}
        CharacterSet::CharacterSet(CharacterClass char_class) : ranges({ CharacterRange(char_class) }), sign(true) {}
        CharacterSet::CharacterSet(const std::unordered_set<CharacterRange> &ranges, bool sign) : ranges(ranges), sign(sign) {}
        
        bool CharacterSet::operator==(const Rule &rule) const {
            const CharacterSet *other = dynamic_cast<const CharacterSet *>(&rule);
            return other && this->operator==(*other);
        }
        
        bool CharacterSet::operator==(const CharacterSet &other) const {
            if (other.sign != sign) return false;
            if (other.ranges != ranges) return false;
            return true;
        }

        size_t CharacterSet::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(to_string());
        }

        rule_ptr CharacterSet::copy() const {
            return std::make_shared<CharacterSet>(*this);
        }

        string CharacterSet::to_string() const {
            string prefix("#<char");
            if (!sign) prefix += " (not)";
            for (auto &range : ranges)
                prefix += " " + range.to_string();
            return prefix + ">";
        }
        
        void CharacterSet::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
