#ifndef COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_

#include <vector>
#include <map>
#include <string>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/rules/symbol.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        class ParseConflictManager {
            const PreparedGrammar parse_grammar;
            const PreparedGrammar lex_grammar;
            std::set<Conflict> conflicts_;

        public:
            ParseConflictManager(const PreparedGrammar &parse_grammar,
                                 const PreparedGrammar &lex_grammar);
            bool resolve_parse_action(const rules::Symbol &symbol,
                                      const ParseAction &old_action,
                                      const ParseAction &new_action);

            void record_conflict(const rules::Symbol &symbol, const ParseAction &left, const ParseAction &right);
            const std::vector<Conflict> conflicts() const;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
