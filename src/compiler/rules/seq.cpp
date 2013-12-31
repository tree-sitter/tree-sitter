#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter {
    namespace rules {
        Seq::Seq(rule_ptr left, rule_ptr right) : left(left), right(right) {};

        bool Seq::operator==(const Rule &rule) const {
            const Seq *other = dynamic_cast<const Seq *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }
        
        string Seq::to_string() const {
            return string("#<seq ") + left->to_string() + " " + right->to_string() + ">";
        }
        
        void Seq::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
