#ifndef __TreeSitter__build_tables__
#define __TreeSitter__build_tables__

#include "parse_table.h"
#include "lex_table.h"

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        std::pair<ParseTable, LexTable> perform(const Grammar &grammar, const Grammar &lex_grammar);
    }
}

#endif
