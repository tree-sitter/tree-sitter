#include "rules.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name) {};

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && (other->name == name);
        }
        
        size_t Symbol::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(name);
        }
        
        rule_ptr Symbol::copy() const {
            return std::make_shared<Symbol>(*this);
        }
        
        string Symbol::to_string() const {
            return string("#<sym '") + name + "'>";
        }
        
        bool Symbol::operator<(const Symbol &other) const {
            return name < other.name;
        }
        
        void Symbol::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}