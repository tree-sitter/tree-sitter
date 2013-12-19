#include "rules.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Blank::Blank() {}
        
        rule_ptr blank() {
            return std::make_shared<Blank>();
        }

        bool Blank::operator==(const Rule &rule) const {
            return dynamic_cast<const Blank *>(&rule) != nullptr;
        }
        
        std::string Blank::to_string() const {
            return "blank";
        }
        
        void Blank::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}