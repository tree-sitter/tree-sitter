#include "compiler/build_tables/build_lex_table.h"
#include "compiler/build_tables/build_parse_table.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace build_tables {

using std::tuple;
using std::vector;
using std::make_tuple;

tuple<ParseTable, LexTable, vector<Conflict>> build_tables(
    const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
  auto parse_table_result = build_parse_table(grammar, lex_grammar);
  ParseTable parse_table = parse_table_result.first;
  vector<Conflict> conflicts = parse_table_result.second;
  LexTable lex_table = build_lex_table(&parse_table, lex_grammar);
  return make_tuple(parse_table, lex_table, conflicts);
}

}  // namespace build_tables
}  // namespace tree_sitter
