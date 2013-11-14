#include "blank.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Blank::Blank() {}
        
        blank_ptr blank() {
            return std::make_shared<Blank>();
        }

        TransitionMap<Rule> Blank::transitions() const {
            return TransitionMap<Rule>();
        }
        
        bool Blank::operator==(const Rule &rule) const {
            return dynamic_cast<const Blank *>(&rule) != NULL;
        }
        
        std::string Blank::to_string() const {
            return "blank";
        }
    }
}