#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/build_tables/build_tables.h"
#include "compiler/generate_code/c_code.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    using std::tuple;
    using std::string;
    using std::vector;
    using std::get;
    using std::make_tuple;

    tuple<string, vector<Conflict>, const GrammarError *>
    compile(const Grammar &grammar, std::string name) {
        auto prepare_grammar_result = prepare_grammar::prepare_grammar(grammar);
        const SyntaxGrammar &syntax_grammar = get<0>(prepare_grammar_result);
        const LexicalGrammar &lexical_grammar = get<1>(prepare_grammar_result);
        const GrammarError *error = get<2>(prepare_grammar_result);

        if (error)
            return make_tuple("", vector<Conflict>(), error);

        auto table_build_result = build_tables::build_tables(syntax_grammar, lexical_grammar);
        const ParseTable &parse_table = get<0>(table_build_result);
        const LexTable &lex_table = get<1>(table_build_result);
        const vector<Conflict> &conflicts = get<2>(table_build_result);

        string code = generate_code::c_code(name, parse_table, lex_table, syntax_grammar, lexical_grammar);

        return make_tuple(code, conflicts, nullptr);
    }
}
