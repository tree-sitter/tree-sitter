#include "rules.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name), is_auxiliary(false) {};
        Symbol::Symbol(const std::string &name, bool is_auxiliary) : name(name), is_auxiliary(is_auxiliary) {};

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && this->operator==(*other);
        }

        bool Symbol::operator==(const Symbol &other) const {
            return (other.name == name) && (other.is_auxiliary == is_auxiliary);
        }

        size_t Symbol::hash_code() const {
            return hash<string>()(name) ^ hash<bool>()(is_auxiliary);
        }
        
        rule_ptr Symbol::copy() const {
            return std::make_shared<Symbol>(*this);
        }
        
        string Symbol::to_string() const {
            return is_auxiliary ?
                string("#<aux_sym '") + name + "'>" :
                string("#<sym '") + name + "'>";
        }
        
        bool Symbol::operator<(const Symbol &other) const {
            if (is_auxiliary < other.is_auxiliary) return true;
            if (is_auxiliary > other.is_auxiliary) return false;
            return (name < other.name);
        }
        
        void Symbol::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}