#ifndef COMPILER_PREPARED_GRAMMAR_H_
#define COMPILER_PREPARED_GRAMMAR_H_

#include <vector>
#include <string>
#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    struct PreparedGrammarOptions {
        std::vector<rules::Symbol> ubiquitous_tokens;
    };

    class PreparedGrammar : public Grammar {
    public:
        PreparedGrammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
                        const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules);
        PreparedGrammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
                        const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules,
                        PreparedGrammarOptions options);

        bool operator==(const PreparedGrammar &other) const;
        const std::string & rule_name(const rules::Symbol &symbol) const;
        const rules::rule_ptr & rule(const rules::Symbol &symbol) const;

        const std::vector<std::pair<std::string, rules::rule_ptr>> aux_rules;
        const PreparedGrammarOptions options;
    };

    std::ostream& operator<<(std::ostream &stream, const PreparedGrammar &grammar);
}

#endif  // COMPILER_PREPARED_GRAMMAR_H_
