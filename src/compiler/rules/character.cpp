#include "rules.h"
#include "transition_map.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        Character::Character(char value) : value(CharMatchSpecific(value)) {};
        Character::Character(CharClass value) : value(CharMatchClass(value)) {};
        Character::Character(char min, char max) : value(CharMatchRange(min, max)) {};
        
        bool Character::operator==(const Rule &rule) const {
            const Character *other = dynamic_cast<const Character *>(&rule);
            return other && (other->value == value);
        }

        size_t Character::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(CharMatchToString(value));
        }

        rule_ptr Character::copy() const {
            return std::make_shared<Character>(*this);
        }

        string Character::to_string() const {
            return string("#<char ") + CharMatchToString(value) + ">";
        }
        
        void Character::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
