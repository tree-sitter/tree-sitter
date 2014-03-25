#ifndef COMPILER_PREPARED_GRAMMAR_H_
#define COMPILER_PREPARED_GRAMMAR_H_

#include <vector>
#include <string>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    class PreparedGrammar : public Grammar {
    public:
        PreparedGrammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
                        const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);
        PreparedGrammar(const Grammar &grammar);

        bool operator==(const PreparedGrammar &other) const;
        bool has_definition(const rules::Symbol &symbol) const;
        const rules::rule_ptr rule(const rules::Symbol &symbol) const;
        size_t index_of(const rules::Symbol &symbol) const;

        const std::vector<std::pair<std::string, rules::rule_ptr>> aux_rules;
    };

    std::ostream& operator<<(std::ostream &stream, const PreparedGrammar &grammar);

    std::string compile(const Grammar &grammar, std::string name);
}

#endif  // COMPILER_PREPARED_GRAMMAR_H_
