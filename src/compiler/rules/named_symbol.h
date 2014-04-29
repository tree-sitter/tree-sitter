#ifndef COMPILER_RULES_NAMED_SYMBOL_H_
#define COMPILER_RULES_NAMED_SYMBOL_H_

#include <string>
#include "compiler/rules/rule.h"

namespace tree_sitter  {
    namespace rules {
        class NamedSymbol : public Rule {
        public:
            explicit NamedSymbol(const std::string &name);

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;

            std::string name;
        };
    }
}

#endif  // COMPILER_RULES_NAMED_SYMBOL_H_
