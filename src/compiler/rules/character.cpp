#include "rules.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        CharacterMatch::CharacterMatch(char character) : type(CharacterMatchTypeSpecific) { value.character = character; }
        CharacterMatch::CharacterMatch(CharacterClass klass) : type(CharacterMatchTypeClass) { value.character_class = klass; }
        CharacterMatch::CharacterMatch(const std::pair<char, char> bounds) : type(CharacterMatchTypeRange) {
            value.range.min_character = bounds.first;
            value.range.max_character = bounds.second;
        }
        
        Character::Character(char character) : matches({ CharacterMatch(character) }), sign(true) {}
        Character::Character(CharacterClass char_class) : matches({ CharacterMatch(char_class) }), sign(true) {}
        Character::Character(const std::vector<CharacterMatch> &matches, bool sign) : matches(matches), sign(sign) {}
        
        bool CharacterMatch::operator==(const CharacterMatch &right) const {
            if (type != right.type)
                return false;
            switch (type) {
                case CharacterMatchTypeClass:
                    return (value.character_class == right.value.character_class);
                case CharacterMatchTypeSpecific:
                    return (value.character == right.value.character);
                case CharacterMatchTypeRange:
                    return (value.range.min_character == right.value.range.min_character &&
                            value.range.max_character == right.value.range.max_character);
            }
        }
        
        string CharacterMatch::to_string() const {
            switch (type) {
                case CharacterMatchTypeClass:
                    switch (value.character_class) {
                        case CharClassDigit:
                            return "<digit>";
                        case CharClassWord:
                            return "<word>";
                    }
                case CharacterMatchTypeSpecific:
                    return (value.character == '\0') ?
                        "<EOF>" :
                        string("'") + value.character + "'";
                case CharacterMatchTypeRange:
                    return (string("'") +
                            value.range.min_character + "'-'" +
                            value.range.max_character + "'");
            }
        }
        
        bool Character::operator==(const Rule &rule) const {
            const Character *other = dynamic_cast<const Character *>(&rule);
            return other && this->operator==(*other);
        }
        
        bool Character::operator==(const Character &other) const {
            if (other.sign != sign) return false;
            auto size = matches.size();
            if (other.matches.size() != size) return false;
            for (int i = 0; i < size; i++)
                if (!(matches[i] == other.matches[i])) return false;
            return true;
        }

        size_t Character::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(to_string());
        }

        rule_ptr Character::copy() const {
            return std::make_shared<Character>(*this);
        }

        string Character::to_string() const {
            string prefix("#<char");
            if (!sign) prefix += " (not)";
            for (auto &match : matches)
                prefix += " " + match.to_string();
            return prefix + ">";
        }
        
        void Character::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
