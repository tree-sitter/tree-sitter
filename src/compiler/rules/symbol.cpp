#include "rules.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name) {};

        sym_ptr sym(const std::string &name) {
            return std::make_shared<Symbol>(name);
        }

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && (other->name == name);
        }
        
        std::string Symbol::to_string() const {
            return std::string("(sym '") + name + "')";
        }
        
        void Symbol::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}