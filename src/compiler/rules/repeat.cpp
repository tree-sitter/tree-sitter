#include "repeat.h"
#include "visitor.h"

using std::string;

namespace tree_sitter {
    namespace rules {
        Repeat::Repeat(const rule_ptr content) : content(content) {}
        
        bool Repeat::operator==(const Rule &rule) const {
            const Repeat *other = dynamic_cast<const Repeat *>(&rule);
            return other && (*other->content == *content);
        }
        
        size_t Repeat::hash_code() const {
            return content->hash_code();
        }
        
        rule_ptr Repeat::copy() const {
            return std::make_shared<Repeat>(*this);
        }
        
        string Repeat::to_string() const {
            return string("#<repeat ") + content->to_string() + ">";
        }
        
        void Repeat::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
