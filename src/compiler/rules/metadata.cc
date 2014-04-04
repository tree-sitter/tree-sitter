#include "compiler/rules/metadata.h"
#include <string>
#include "compiler/rules/visitor.h"
#include <map>

namespace tree_sitter  {
    using std::hash;
    using std::make_shared;

    namespace rules {
        Metadata::Metadata(rule_ptr rule, MetadataValue value) : rule(rule), value(value) {}

        bool Metadata::operator==(const Rule &rule) const {
            auto other = dynamic_cast<const Metadata *>(&rule);
            return other && other->value == value && other->rule->operator==(*this->rule);
        }

        size_t Metadata::hash_code() const {
            return hash<int>()(value);
        }

        rule_ptr Metadata::copy() const {
            return make_shared<Metadata>(rule, value);
        }

        std::string Metadata::to_string() const {
            return "#<metadata " + rule->to_string() + ">";
        }

        void Metadata::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}