#ifndef COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_

#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        class ConflictManager {
            const PreparedGrammar parse_grammar;
            const PreparedGrammar lex_grammar;
            std::vector<Conflict> conflicts_;

        public:
            ConflictManager(const PreparedGrammar &parse_grammar, const PreparedGrammar &lex_grammar);

            LexAction resolve_lex_action(const LexAction &left, const LexAction &right);
            ParseAction resolve_parse_action(const rules::Symbol &symbol, ParseAction left, ParseAction right);

            void record_conflict(const rules::Symbol &symbol, const ParseAction &left, const ParseAction &right);
            const std::vector<Conflict> & conflicts() const;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
