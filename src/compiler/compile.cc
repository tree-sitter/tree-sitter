#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/build_tables/build_tables.h"
#include "compiler/generate_code/c_code.h"
#include "compiler/prepared_grammar.h"
#include "compiler/name_symbols/name_symbols.h"

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::vector;

    pair<string, vector<Conflict>> compile(const Grammar &grammar, std::string name) {
        auto grammars = prepare_grammar::prepare_grammar(grammar);
        PreparedGrammar &syntax_grammar = grammars.first;
        PreparedGrammar &lexical_grammar = grammars.second;

        auto table_build_result = build_tables::build_tables(syntax_grammar, lexical_grammar);
        auto tables = table_build_result.first;
        auto conflicts = table_build_result.second;
        ParseTable &parse_table = tables.first;
        LexTable &lex_table = tables.second;

        auto symbol_names = name_symbols::name_symbols(parse_table.symbols, lexical_grammar);
        return { generate_code::c_code(name, parse_table, lex_table, symbol_names), conflicts };
    }
}
