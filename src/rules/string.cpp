#include "string.h"
#include "transition_map.h"
#include "char.h"
#include "seq.h"

namespace tree_sitter  {
    namespace rules {
        String::String(std::string value) : value(value) {};
        
        TransitionMap<Rule> String::transitions() const {
            auto result = rule_ptr(new Char(value[0]));
            for (int i = 1; i < value.length(); i++)
                result = rule_ptr(new Seq(result, rule_ptr(new Char(value[i]))));
            return result->transitions();
        }
        
        bool String::operator==(const Rule &rule) const {
            const String *other = dynamic_cast<const String *>(&rule);
            return (other != NULL) && (other->value == value);
        }
        
        String * String::copy() const {
            return new String(value);
        }
        
        std::string String::to_string() const {
            return std::string("(string '") + value + "')";
        }        
    }
}