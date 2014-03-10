#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/build_tables/build_tables.h"
#include "compiler/generate_code/c_code.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    std::string compile(const Grammar &grammar, std::string name) {
        auto grammars = prepare_grammar::prepare_grammar(grammar);
        auto tables = build_tables::build_tables(grammars.first, grammars.second);
        return generate_code::c_code(name, tables.first, tables.second);
    }
}
