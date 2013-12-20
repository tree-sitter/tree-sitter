#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name) {};

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && (other->name == name);
        }
        
        string Symbol::to_string() const {
            return string("(sym '") + name + "')";
        }
        
        void Symbol::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}