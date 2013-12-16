#include "string.h"
#include "transition_map.h"
#include "char.h"
#include "seq.h"

namespace tree_sitter  {
    namespace rules {
        String::String(std::string value) : value(value) {};
        
        string_ptr str(const std::string &value) {
            return std::make_shared<String>(value);
        }

        TransitionMap<Rule> String::transitions() const {
            rule_ptr result = character(value[0]);
            for (int i = 1; i < value.length(); i++)
                result = seq({ result, character(value[i]) });
            return result->transitions();
        }
        
        bool String::operator==(const Rule &rule) const {
            const String *other = dynamic_cast<const String *>(&rule);
            return (other != NULL) && (other->value == value);
        }
                
        std::string String::to_string() const {
            return std::string("(string '") + value + "')";
        }        

    }
}