#ifndef COMPILER_BUILD_TABLES_BUILD_TABLES_H_
#define COMPILER_BUILD_TABLES_BUILD_TABLES_H_

#include <string>
#include <tuple>
#include <vector>
#include "compiler/parse_table.h"
#include "compiler/lex_table.h"
#include "compiler/compile_error.h"

namespace tree_sitter {

struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

std::tuple<ParseTable, LexTable, CompileError> build_tables(
  const SyntaxGrammar &, const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_BUILD_TABLES_H_
