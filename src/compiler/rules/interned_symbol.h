#ifndef COMPILER_RULES_INTERNED_SYMBOL_H_
#define COMPILER_RULES_INTERNED_SYMBOL_H_

#include "compiler/rules/symbol.h"

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            SymbolOptionToken = 1 << 0,
            SymbolOptionAuxiliary = 1 << 1,
        } SymbolOption;
        
        class ISymbol : public Rule {
        public:
            explicit ISymbol(int index);
            ISymbol(int index, SymbolOption options);
            
            bool operator==(const ISymbol &other) const;
            bool operator==(const Rule &other) const;
            
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;
            bool operator<(const ISymbol &other) const;
            
            bool is_token() const;
            bool is_built_in() const;
            bool is_auxiliary() const;
            
            int index;
            SymbolOption options;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::ISymbol> {
        size_t operator()(const tree_sitter::rules::ISymbol &rule) const {
            return rule.hash_code();
        }
    };
}

#endif  // COMPILER_RULES_INTERNED_SYMBOL_H_
