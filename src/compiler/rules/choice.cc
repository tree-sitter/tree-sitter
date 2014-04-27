#include "compiler/rules/choice.h"
#include <string>
#include <set>
#include "compiler/rules/visitor.h"

namespace tree_sitter  {
    using std::string;
    using std::make_shared;
    using std::vector;
    using std::set;
    using std::dynamic_pointer_cast;

    namespace rules {
        Choice::Choice(const vector<rule_ptr> &elements) : elements(elements) {}

        rule_ptr Choice::Build(const vector<rule_ptr> &elements) {
            return make_shared<Choice>(elements);
        }

        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            if (!other) return false;
            size_t size = elements.size();
            if (size != other->elements.size()) return false;
            for (size_t i = 0; i < size; i++)
                if (!elements[i]->operator==(*other->elements[i])) return false;
            return true;
        }

        size_t Choice::hash_code() const {
            size_t result = std::hash<size_t>()(elements.size());
            for (const auto &element : elements)
                result ^= element->hash_code();
            return result;
        }

        rule_ptr Choice::copy() const {
            return std::make_shared<Choice>(*this);
        }

        string Choice::to_string() const {
            string result = "#<choice";
            for (const auto &element : elements)
                result += " " + element->to_string();
            return result + ">";
        }

        void Choice::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}
