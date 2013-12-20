#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter {
    namespace rules {
        Repeat::Repeat(const rule_ptr content) : content(content) {}
        
        bool Repeat::operator==(const Rule &rule) const {
            const Repeat *other = dynamic_cast<const Repeat *>(&rule);
            return other && (*other->content == *content);
        }
        
        string Repeat::to_string() const {
            return string("(repeat ") + content->to_string() + ")";
        }
        
        void Repeat::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}
