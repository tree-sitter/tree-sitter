#include "char.h"
#include "blank.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter  {
    namespace rules {
        Char::Char(char value) : value(value) {};

        TransitionMap<Rule> Char::transitions() const {
            return TransitionMap<Rule>({ rule_ptr(new Char(value)) }, { rule_ptr(new Blank()) });
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
