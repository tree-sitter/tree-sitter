#ifndef __tree_sitter__code_generator__
#define __tree_sitter__code_generator__

#include "grammar.h"
#include "parse_table.h"
#include "lex_table.h"

namespace tree_sitter {
    namespace code_gen {
        std::string c_code(const Grammar &grammar, const lr::ParseTable &parse_table, const lr::LexTable &lex_table);
    }
}

#endif
