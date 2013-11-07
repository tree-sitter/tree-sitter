#include "symbol.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(int id) : id(id) {};

        TransitionMap<Rule> Symbol::transitions() const {
            return TransitionMap<Rule>({ copy() }, { new Blank() });
        }
        
        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return (other != NULL) && (other->id == id);
        }
        
        Symbol * Symbol::copy() const {
            return new Symbol(id);
        }
        
        std::string Symbol::to_string() const {
            return std::to_string(id);
        }        
    }
}