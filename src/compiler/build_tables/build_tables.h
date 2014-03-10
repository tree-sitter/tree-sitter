#ifndef __TreeSitter__build_tables__
#define __TreeSitter__build_tables__

#include "parse_table.h"
#include "lex_table.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace build_tables {
        std::pair<ParseTable, LexTable> build_tables(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar);
    }
}

#endif
