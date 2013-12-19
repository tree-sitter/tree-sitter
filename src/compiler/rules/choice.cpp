#include "rules.h"
#include "transition_map.h"

namespace tree_sitter  {
    namespace rules {
        Choice::Choice(rule_ptr left, rule_ptr right) : left(left), right(right) {};
        
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules) {
            rule_ptr result;
            for (auto rule : rules)
                result = result.get() ? std::make_shared<Choice>(result, rule) : rule;
            return result;
        }

        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }

        std::string Choice::to_string() const {
            return std::string("(choice ") + left->to_string() + " " + right->to_string() + ")";
        }
        
        void Choice::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}