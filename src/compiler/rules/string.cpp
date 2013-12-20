#include "rules.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        String::String(std::string value) : value(value) {};
        
        rule_ptr str(const std::string &value) {
            return std::make_shared<String>(value);
        }

        bool String::operator==(const Rule &rule) const {
            const String *other = dynamic_cast<const String *>(&rule);
            return (other != NULL) && (other->value == value);
        }
                
        std::string String::to_string() const {
            return std::string("(string '") + value + "')";
        }        
        
        void String::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}