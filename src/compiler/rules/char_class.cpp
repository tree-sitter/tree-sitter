#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        CharClass::CharClass(CharClassType value) : value(value) {};
        
        bool CharClass::operator==(const Rule &rule) const {
            const CharClass *other = dynamic_cast<const CharClass *>(&rule);
            return other && (other->value == value);
        }
        
        string CharClass::to_string() const {
            switch (value) {
                case CharClassTypeDigit:
                    return "<digit>";
                case CharClassTypeWord:
                    return "<word>";
            }
        }
        
        void CharClass::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
