#ifndef COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_

#include <vector>
#include <map>
#include <string>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/rules/interned_symbol.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        class ConflictManager {
            const PreparedGrammar parse_grammar;
            const PreparedGrammar lex_grammar;
            std::set<Conflict> conflicts_;

        public:
            ConflictManager(const PreparedGrammar &parse_grammar,
                            const PreparedGrammar &lex_grammar);

            bool resolve_lex_action(const LexAction &old_action,
                                    const LexAction &new_action);
            bool resolve_parse_action(const rules::ISymbol &symbol,
                                      const ParseAction &old_action,
                                      const ParseAction &new_action);

            void record_conflict(const rules::ISymbol &symbol, const ParseAction &left, const ParseAction &right);
            const std::vector<Conflict> conflicts() const;
        };
    }
}

#endif  // COMPILER_BUILD_TABLES_CONFLICT_MANAGER_H_
