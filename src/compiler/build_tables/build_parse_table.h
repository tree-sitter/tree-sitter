#ifndef COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_
#define COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_

#include <utility>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        std::pair<ParseTable, std::vector<Conflict>>
        build_parse_table(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar);
    }
}

#endif  // COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_
