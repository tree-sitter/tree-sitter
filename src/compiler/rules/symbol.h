#ifndef COMPILER_RULES_SYMBOL_H_
#define COMPILER_RULES_SYMBOL_H_

#include <string>
#include <utility>
#include "compiler/rules/rule.h"

namespace tree_sitter  {
    namespace rules {
        typedef enum {
            SymbolTypeNormal,
            SymbolTypeHidden,
            SymbolTypeAuxiliary,
            SymbolTypeBuiltIn
        } SymbolType;

        class Symbol : public Rule {
        public:
            Symbol(const std::string &name);
            Symbol(const std::string &name, SymbolType type);

            bool operator==(const Rule& other) const;
            bool operator==(const Symbol &other) const;

            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;
            bool operator<(const Symbol &other) const;

            bool is_built_in() const;
            bool is_hidden() const;
            bool is_auxiliary() const;

            std::string name;
            SymbolType type;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::Symbol> {
        size_t operator()(const tree_sitter::rules::Symbol &rule) const {
            return rule.hash_code();
        }
    };
}

#endif  // COMPILER_RULES_SYMBOL_H_
