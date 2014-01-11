#ifndef __TreeSitter__parse_table_builder__
#define __TreeSitter__parse_table_builder__

#include "parse_table.h"
#include "lex_table.h"

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::pair<ParseTable, LexTable> perform(const Grammar &grammar, const Grammar &lex_grammar);
    }
}

#endif
