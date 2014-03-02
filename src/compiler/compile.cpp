#include "tree_sitter/compiler.h"
#include "prepare_grammar/prepare_grammar.h"
#include "build_tables/build_tables.h"
#include "generate_code/c_code.h"
#include "prepared_grammar.h"

namespace tree_sitter {
    std::string compile(const Grammar &grammar, std::string name) {
        auto grammars = prepare_grammar::prepare_grammar(grammar);
        auto tables = build_tables::build_tables(grammars.first, grammars.second);
        return generate_code::c_code(name, tables.first, tables.second);
    }
}
