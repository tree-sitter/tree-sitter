#include "symbol.h"
#include "blank.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name) {};
        Symbol::Symbol(const char *name) : name(name) {};

        TransitionMap<Rule> Symbol::transitions() const {
            return TransitionMap<Rule>({ rule_ptr(new Symbol(name)) }, { rule_ptr(new Blank()) });
        }
        
        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return (other != NULL) && (other->name == name);
        }
        
        std::string Symbol::to_string() const {
            return name;
        }
    }
}