#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        String::String(string value) : value(value) {};
        
        bool String::operator==(const Rule &rule) const {
            const String *other = dynamic_cast<const String *>(&rule);
            return (other != NULL) && (other->value == value);
        }
                
        string String::to_string() const {
            return string("(string '") + value + "')";
        }        
        
        void String::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}