#ifndef COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_
#define COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_

#include <utility>
#include <vector>
#include "compiler/parse_table.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {

class SyntaxGrammar;
class LexicalGrammar;

namespace build_tables {

std::pair<ParseTable, const GrammarError *>
build_parse_table(const SyntaxGrammar &, const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_BUILD_PARSE_TABLE_H_
