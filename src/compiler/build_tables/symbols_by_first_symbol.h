#ifndef COMPILER_BUILD_TABLES_SYMBOLS_BY_FIRST_SYMBOL_H_
#define COMPILER_BUILD_TABLES_SYMBOLS_BY_FIRST_SYMBOL_H_

#include <map>
#include <set>
#include "compiler/rules/symbol.h"

namespace tree_sitter {

struct SyntaxGrammar;

namespace build_tables {

std::map<rules::Symbol, std::set<rules::Symbol>> symbols_by_first_symbol(
  const SyntaxGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_SYMBOLS_BY_FIRST_SYMBOL_H_
