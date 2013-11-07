#include "char.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter  {
    namespace rules {
        Char::Char(char value) : value(value) {};
        
        TransitionMap<Rule> Char::transitions() const {
            return TransitionMap<Rule>({ copy() }, { new Blank() });
        }
        
        bool Char::operator==(const Rule &rule) const {
            const Char *other = dynamic_cast<const Char *>(&rule);
            return (other != NULL) && (other->value == value);
        }
        
        Char * Char::copy() const {
            return new Char(value);
        }
        
        string Char::to_string() const {
            return std::to_string(value);
        }
    }
}