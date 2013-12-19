#include "rules.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace rules {
        Repeat::Repeat(const rule_ptr content) : content(content) {}
        
        rule_ptr repeat(const rule_ptr content) {
            return std::make_shared<Repeat>(content);
        }
        
        bool Repeat::operator==(const Rule &rule) const {
            const Repeat *other = dynamic_cast<const Repeat *>(&rule);
            return other && (*other->content == *content);
        }
        
        std::string Repeat::to_string() const {
            return std::string("(repeat ") + content->to_string() + ")";
        }
        
        void Repeat::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}
