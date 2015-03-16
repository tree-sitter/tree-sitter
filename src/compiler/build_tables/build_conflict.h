#ifndef COMPILER_BUILD_TABLES_BUILD_CONFLICT_H_
#define COMPILER_BUILD_TABLES_BUILD_CONFLICT_H_

#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/rules/symbol.h"
#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {

class SyntaxGrammar;
class LexicalGrammar;

namespace build_tables {

std::string build_conflict(const ParseAction &, const ParseAction &,
                           const ParseItemSet &, const rules::Symbol &,
                           const SyntaxGrammar &, const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_BUILD_CONFLICT_H_
