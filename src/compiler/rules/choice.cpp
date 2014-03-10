#include "choice.h"
#include "visitor.h"

namespace tree_sitter  {
    using std::string;
    using std::make_shared;
    using std::vector;

    namespace rules {
        Choice::Choice(rule_ptr left, rule_ptr right) : left(left), right(right) {};

        rule_ptr Choice::Build(const vector<rule_ptr> &rules) {
            rule_ptr result;
            for (auto rule : rules)
                result = result.get() ? make_shared<Choice>(result, rule) : rule;
            return result;
        }

        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }

        size_t Choice::hash_code() const {
            return left->hash_code() ^ right->hash_code();
        }

        rule_ptr Choice::copy() const {
            return std::make_shared<Choice>(*this);
        }

        string Choice::to_string() const {
            return string("#<choice ") + left->to_string() + " " + right->to_string() + ">";
        }

        void Choice::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}