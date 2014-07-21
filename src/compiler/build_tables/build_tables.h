#ifndef COMPILER_BUILD_TABLES_BUILD_TABLES_H_
#define COMPILER_BUILD_TABLES_BUILD_TABLES_H_

#include <utility>
#include <vector>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/lex_table.h"

namespace tree_sitter {
class SyntaxGrammar;
class LexicalGrammar;

namespace build_tables {
std::tuple<ParseTable, LexTable, std::vector<Conflict> > build_tables(
    const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar);
}
}

#endif  // COMPILER_BUILD_TABLES_BUILD_TABLES_H_
