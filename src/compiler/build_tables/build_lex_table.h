#ifndef COMPILER_BUILD_TABLES_BUILD_LEX_TABLE_H_
#define COMPILER_BUILD_TABLES_BUILD_LEX_TABLE_H_

#include "tree_sitter/compiler.h"
#include "compiler/lex_table.h"

namespace tree_sitter {

class LexicalGrammar;
class ParseTable;

namespace build_tables {

LexTable build_lex_table(ParseTable *, const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_BUILD_LEX_TABLE_H_
