#include "char.h"
#include "blank.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter  {
    namespace rules {
        Char::Char(char value) : value(value) {};
        
        char_ptr character(char value) {
            return std::make_shared<Char>(value);
        }

        TransitionMap<Rule> Char::transitions() const {
            return TransitionMap<Rule>({ character(value) }, { blank() });
        }

        bool Char::operator==(const Rule &rule) const {
            const Char *other = dynamic_cast<const Char *>(&rule);
            return (other != nullptr) && (other->value == value);
        }

        string Char::to_string() const {
            return std::string("'") + &value + "'";
        }
    }
}
