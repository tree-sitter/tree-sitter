#ifndef COMPILER_BUILD_TABLES_BUILD_TABLES_H_
#define COMPILER_BUILD_TABLES_BUILD_TABLES_H_

#include <utility>
#include "compiler/parse_table.h"
#include "compiler/lex_table.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        std::pair<ParseTable, LexTable> build_tables(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar);
    }
}

#endif  // COMPILER_BUILD_TABLES_BUILD_TABLES_H_
