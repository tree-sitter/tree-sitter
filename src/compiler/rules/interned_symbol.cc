#include "compiler/rules/interned_symbol.h"
#include <map>
#include <string>
#include "compiler/rules/visitor.h"

namespace tree_sitter  {
    using std::string;
    using std::to_string;
    using std::hash;
    
    namespace rules {
        ISymbol::ISymbol(int index) :
            index(index),
            options(SymbolOption(0)) {}
        
        ISymbol::ISymbol(int index, SymbolOption options) :
            index(index),
            options(options) {}
        
        bool ISymbol::operator==(const ISymbol &other) const {
            return (other.index == index) && (other.options == options);
        }

        bool ISymbol::operator==(const Rule &rule) const {
            const ISymbol *other = dynamic_cast<const ISymbol *>(&rule);
            return other && this->operator==(*other);
        }
        
        size_t ISymbol::hash_code() const {
            return hash<int>()(index) ^ hash<int16_t>()(options);
        }
        
        rule_ptr ISymbol::copy() const {
            return std::make_shared<ISymbol>(*this);
        }
        
        string ISymbol::to_string() const {
            string name = (options & SymbolOptionAuxiliary) ? "aux_" : "";
            name += (options & SymbolOptionToken) ? "token" : "sym";
            return "#<" + name + std::to_string(index) + ">";
        }
        
        bool ISymbol::operator<(const ISymbol &other) const {
            if (options < other.options) return true;
            if (options > other.options) return false;
            return (index < other.index);
        }
        
        bool ISymbol::is_token() const {
            return options & SymbolOptionToken;
        }
        
        bool ISymbol::is_built_in() const {
            return index < 0;
        }
        
        bool ISymbol::is_auxiliary() const {
            return options & SymbolOptionAuxiliary;
        }
        
        void ISymbol::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}
