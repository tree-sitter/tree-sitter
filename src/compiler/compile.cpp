#include "compile.h"

#include "grammar.h"
#include "prepare_grammar/perform.h"
#include "build_tables/perform.h"
#include "generate_code/c_code.h"

namespace tree_sitter {
    std::string compile(const Grammar &grammar) {
        auto grammars = prepare_grammar::perform(grammar);
        auto tables = build_tables::perform(grammars.first, grammars.second);
        auto rule_names = grammars.first.rule_names();
        auto token_names = grammars.second.rule_names();
        rule_names.insert(rule_names.end(), token_names.begin(), token_names.end());
        return generate_code::c_code(rule_names, tables.first, tables.second);
    }
}
