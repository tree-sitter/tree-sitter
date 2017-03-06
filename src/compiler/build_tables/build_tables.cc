#include "compiler/build_tables/build_tables.h"
#include <tuple>
#include "compiler/build_tables/lex_table_builder.h"
#include "compiler/build_tables/build_parse_table.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/compile_error.h"

namespace tree_sitter {
namespace build_tables {

using std::string;
using std::tuple;
using std::vector;
using std::make_tuple;

tuple<ParseTable, LexTable, CompileError> build_tables(
  const SyntaxGrammar &grammar,
  const LexicalGrammar &lexical_grammar
) {
  auto parse_table_result = build_parse_table(grammar, lexical_grammar);
  ParseTable parse_table = parse_table_result.first;
  const CompileError error = parse_table_result.second;
  LexTable lex_table = LexTableBuilder::create(lexical_grammar)->build(&parse_table);
  return make_tuple(parse_table, lex_table, error);
}

}  // namespace build_tables
}  // namespace tree_sitter
