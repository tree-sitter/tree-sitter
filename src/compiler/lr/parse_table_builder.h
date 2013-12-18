#ifndef __TreeSitter__parse_table_builder__
#define __TreeSitter__parse_table_builder__

#include "parse_table.h"

namespace tree_sitter {
    class Grammar;
    
    namespace lr {
        ParseTable build_tables(const Grammar &grammar);
    }
}

#endif
