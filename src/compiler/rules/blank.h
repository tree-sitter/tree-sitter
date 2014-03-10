#ifndef COMPILER_RULES_BLANK_H_
#define COMPILER_RULES_BLANK_H_

#include <string>
#include "compiler/rules/rule.h"

namespace tree_sitter  {
    namespace rules {
        class Blank : public Rule {
        public:
            Blank();

            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor *visitor) const;
        };
    }
}

#endif  // COMPILER_RULES_BLANK_H_
