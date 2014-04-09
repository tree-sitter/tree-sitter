#ifndef COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_

#include <vector>
#include <map>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        class ConflictManager {
            const PreparedGrammar parse_grammar;
            const PreparedGrammar lex_grammar;
            const std::map<rules::Symbol, std::string> rule_names;
            std::vector<Conflict> conflicts_;

        public:
            ConflictManager(const PreparedGrammar &parse_grammar,
                            const PreparedGrammar &lex_grammar,
                            const std::map<rules::Symbol, std::string> &rule_names);

            bool resolve_lex_action(const LexAction &old_action,
                                    const LexAction &new_action);
            bool resolve_parse_action(const rules::Symbol &symbol,
                                      const ParseAction &old_action,
                                      const ParseAction &new_action);

            void record_conflict(const rules::Symbol &symbol, const ParseAction &left, const ParseAction &right);
            const std::vector<Conflict> & conflicts() const;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
