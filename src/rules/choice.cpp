#include "choice.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Choice::Choice(const Rule &left, const Rule &right) : left(left.copy()), right(right.copy()) {};
        Choice::Choice(rule_ptr left, rule_ptr right) : left(left), right(right) {};
        
        TransitionMap<Rule> Choice::transitions() const {
            auto result = left->transitions();
            result.merge(right->transitions(), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                return rule_ptr(new Choice(left, right));
            });
            return result;
        }

        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            return (other != NULL) && (*other->left == *left) && (*other->right == *right);
        }

        Choice * Choice::copy() const {
            return new Choice(left, right);
        }
        
        std::string Choice::to_string() const {
            return std::string("(choice ") + left->to_string() + " " + right->to_string() + ")";
        }
    }
}