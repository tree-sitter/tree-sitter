#ifndef __tree_sitter__code_generator__
#define __tree_sitter__code_generator__

#include "grammar.h"
#include "parse_table.h"
#include "lex_table.h"

namespace tree_sitter {
    namespace generate_code {
        std::string c_code(std::vector<std::string> rule_names, const ParseTable &parse_table, const LexTable &lex_table);
    }
}

#endif
