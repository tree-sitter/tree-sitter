#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        Character::Character(char value) : value(CharMatchSpecific(value)) {};
        Character::Character(CharClass value) : value(CharMatchClass(value)) {};
        Character::Character(char min, char max) : value(CharMatchRange(min, max)) {};
        
        bool Character::operator==(const Rule &rule) const {
            const Character *other = dynamic_cast<const Character *>(&rule);
            return other && (other->value == value);
        }

        string Character::to_string() const {
            return string("#<char ") + CharMatchToString(value) + ">";
        }
        
        void Character::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
