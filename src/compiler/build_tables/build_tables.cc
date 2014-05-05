#include "compiler/build_tables/build_tables.h"
#include "compiler/build_tables/build_parse_table.h"
#include "compiler/build_tables/build_lex_table.h"

namespace tree_sitter {
    using std::tuple;
    using std::vector;
    using std::make_tuple;

    namespace build_tables {
        tuple<ParseTable, LexTable, vector<Conflict>>
        build_tables(const PreparedGrammar &grammar,
                     const PreparedGrammar &lex_grammar) {
            auto parse_table_result = build_parse_table(grammar, lex_grammar);
            ParseTable parse_table = parse_table_result.first;
            vector<Conflict> conflicts = parse_table_result.second;
            auto lex_table = build_lex_table(&parse_table, lex_grammar);
            return make_tuple(parse_table, lex_table, conflicts);
        }
    }
}
