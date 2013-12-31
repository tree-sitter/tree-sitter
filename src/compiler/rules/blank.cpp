#include "rules.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Blank::Blank() {}
        
        bool Blank::operator==(const Rule &rule) const {
            return dynamic_cast<const Blank *>(&rule) != nullptr;
        }
        
        std::string Blank::to_string() const {
            return "#<blank>";
        }
        
        void Blank::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}