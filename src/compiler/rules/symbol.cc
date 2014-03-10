#include "compiler/rules/symbol.h"
#include <map>
#include "compiler/rules/visitor.h"

namespace tree_sitter  {
    using std::string;
    using std::hash;
    
    namespace rules {
        Symbol::Symbol(const std::string &name) : name(name), type(SymbolTypeNormal) {}
        Symbol::Symbol(const std::string &name, SymbolType type) : name(name), type(type) {}

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && this->operator==(*other);
        }

        bool Symbol::operator==(const Symbol &other) const {
            return (other.name == name) && (other.type == type);
        }

        size_t Symbol::hash_code() const {
            return hash<string>()(name) ^ hash<short int>()(type);
        }

        rule_ptr Symbol::copy() const {
            return std::make_shared<Symbol>(*this);
        }

        string Symbol::to_string() const {
            switch (type) {
                case SymbolTypeNormal:
                    return string("#<sym '") + name + "'>";
                case SymbolTypeHidden:
                    return string("#<hidden_sym '") + name + "'>";
                case SymbolTypeAuxiliary:
                    return string("#<aux_sym '") + name + "'>";
                case SymbolTypeBuiltIn:
                    return string("#<builtin_sym '") + name + "'>";
            }
        }

        bool Symbol::operator<(const Symbol &other) const {
            if (type < other.type) return true;
            if (type > other.type) return false;
            return (name < other.name);
        }

        bool Symbol::is_built_in() const {
            return type == SymbolTypeBuiltIn;
        }

        bool Symbol::is_auxiliary() const {
            return type == SymbolTypeAuxiliary;
        }

        bool Symbol::is_hidden() const {
            return (type == SymbolTypeHidden || type == SymbolTypeAuxiliary);
        }

        void Symbol::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}