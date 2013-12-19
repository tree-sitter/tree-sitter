#include "rules.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter  {
    namespace rules {
        CharClass::CharClass(CharClassType value) : value(value) {};
        
        rule_ptr char_class(CharClassType type) {
            return std::make_shared<CharClass>(type);
        }
        
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
        
        void CharClass::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}
