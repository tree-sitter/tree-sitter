#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        Char::Char(char value) : value(value) {};
        
        bool Char::operator==(const Rule &rule) const {
            const Char *other = dynamic_cast<const Char *>(&rule);
            return other && (other->value == value);
        }

        string Char::to_string() const {
            return string("'") + value + "'";
        }
        
        void Char::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
