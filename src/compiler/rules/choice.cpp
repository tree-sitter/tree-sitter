#include "rules.h"
#include "transition_map.h"

using std::string;

namespace tree_sitter  {
    namespace rules {
        Choice::Choice(rule_ptr left, rule_ptr right) : left(left), right(right) {};
        
        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }

        size_t Choice::hash_code() const {
            return typeid(this).hash_code() ^ left->hash_code() ^ right->hash_code();
        }
        
        string Choice::to_string() const {
            return string("#<choice ") + left->to_string() + " " + right->to_string() + ">";
        }
        
        void Choice::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}