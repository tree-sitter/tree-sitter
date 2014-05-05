#ifndef COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_

#include "tree_sitter/compiler.h"
#include "compiler/lex_table.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        class LexConflictManager {
            const PreparedGrammar grammar;

        public:
            explicit LexConflictManager(const PreparedGrammar &grammar);
            bool resolve_lex_action(const LexAction &old_action,
                                    const LexAction &new_action);
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
