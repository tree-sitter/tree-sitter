#ifndef __tree_sitter__code_generator__
#define __tree_sitter__code_generator__

#include "compiler/parse_table.h"
#include "compiler/lex_table.h"

namespace tree_sitter {
    namespace generate_code {
        std::string c_code(std::string name, const ParseTable &parse_table, const LexTable &lex_table);
    }
}

#endif
