#include "compiler/rules/symbol.h"
#include <map>
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter  {
    using std::string;
    using std::to_string;
    using std::hash;

    namespace rules {
        Symbol::Symbol(int index) :
            index(index),
            options(SymbolOption(0)) {}

        Symbol::Symbol(int index, SymbolOption options) :
            index(index),
            options(options) {}

        bool Symbol::operator==(const Symbol &other) const {
            return (other.index == index) && (other.options == options);
        }

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return other && this->operator==(*other);
        }

        size_t Symbol::hash_code() const {
            return hash<int>()(index) ^ hash<int16_t>()(options);
        }

        rule_ptr Symbol::copy() const {
            return std::make_shared<Symbol>(*this);
        }

        string Symbol::to_string() const {
            string name = (options & SymbolOptionAuxiliary) ? "aux_" : "";
            name += (options & SymbolOptionToken) ? "token" : "sym";
            return "#<" + name + std::to_string(index) + ">";
        }

        bool Symbol::operator<(const Symbol &other) const {
            if (options < other.options) return true;
            if (options > other.options) return false;
            return (index < other.index);
        }

        bool Symbol::is_token() const {
            return options & SymbolOptionToken;
        }

        bool Symbol::is_built_in() const {
            return index < 0;
        }

        bool Symbol::is_auxiliary() const {
            return options & SymbolOptionAuxiliary;
        }

        void Symbol::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}
