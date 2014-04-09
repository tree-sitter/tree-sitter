#ifndef COMPILER_BUILD_TABLES_BUILD_TABLES_H_
#define COMPILER_BUILD_TABLES_BUILD_TABLES_H_

#include <utility>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/lex_table.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        std::pair<std::pair<ParseTable, LexTable>, std::vector<Conflict>>
        build_tables(const PreparedGrammar &grammar, 
                     const PreparedGrammar &lex_grammar,
                     const std::map<rules::Symbol, std::string> &rule_names);
    }
}

#endif  // COMPILER_BUILD_TABLES_BUILD_TABLES_H_
