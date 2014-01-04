#include "rules.h"
#include "transition_map.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        NonTerminal::NonTerminal(const std::string &name) : Symbol(name) {};
        
        bool NonTerminal::operator==(const Rule &rule) const {
            const NonTerminal *other = dynamic_cast<const NonTerminal *>(&rule);
            return other && (other->name == name);
        }
        
        rule_ptr NonTerminal::copy() const {
            return std::make_shared<NonTerminal>(*this);
        }
        
        string NonTerminal::to_string() const {
            return string("#<non-terminal '") + name + "'>";
        }
        
        void NonTerminal::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}