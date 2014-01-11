#include "rules.h"

using std::string;

namespace tree_sitter {
    namespace rules {
        Seq::Seq(rule_ptr left, rule_ptr right) : left(left), right(right) {};

        bool Seq::operator==(const Rule &rule) const {
            const Seq *other = dynamic_cast<const Seq *>(&rule);
            return other && (*other->left == *left) && (*other->right == *right);
        }
        
        size_t Seq::hash_code() const {
            return typeid(this).hash_code() ^ left->hash_code() ^ right->hash_code();
        }
        
        rule_ptr Seq::copy() const {
            return std::make_shared<Seq>(*this);
        }
        
        string Seq::to_string() const {
            return string("#<seq ") + left->to_string() + " " + right->to_string() + ">";
        }
        
        void Seq::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
