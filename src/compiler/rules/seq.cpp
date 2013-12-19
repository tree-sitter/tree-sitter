#include "rules.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace rules {
        Seq::Seq(rule_ptr left, rule_ptr right) : left(left), right(right) {};

        rule_ptr seq(const std::initializer_list<rule_ptr> &rules) {
            rule_ptr result;
            for (auto rule : rules)
                result = (result.get() && typeid(*result) != typeid(Blank)) ?
                    std::make_shared<Seq>(result, rule) :
                    rule;
            return result;
        }

        bool Seq::operator==(const Rule &rule) const {
            const Seq *other = dynamic_cast<const Seq *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }
        
        std::string Seq::to_string() const {
            return std::string("(seq ") + left->to_string() + " " + right->to_string() + ")";
        }
        
        void Seq::accept(RuleVisitor &visitor) const {
            visitor.visit(this);
        }
    }
}
