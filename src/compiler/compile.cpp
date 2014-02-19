#include "tree_sitter/compiler.h"
#include "prepare_grammar/perform.h"
#include "build_tables/perform.h"
#include "generate_code/c_code.h"
#include "prepared_grammar.h"

namespace tree_sitter {
    std::string compile(const Grammar &grammar, std::string name) {
        auto grammars = prepare_grammar::perform(grammar);
        auto tables = build_tables::perform(grammars.first, grammars.second);
        return generate_code::c_code(name, tables.first, tables.second);
    }
}
