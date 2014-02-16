#include "rules.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        String::String(string value) : value(value) {};
        
        bool String::operator==(const Rule &rule) const {
            const String *other = dynamic_cast<const String *>(&rule);
            return (other != NULL) && (other->value == value);
        }
                
        size_t String::hash_code() const {
            return hash<string>()(value);
        }
        
        rule_ptr String::copy() const {
            return std::make_shared<String>(*this);
        }
        
        string String::to_string() const {
            return string("#<string '") + value + "'>";
        }        
        
        void String::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}