#ifndef COMPILER_BUILD_TABLES_FIRST_SYMBOLS_H_
#define COMPILER_BUILD_TABLES_FIRST_SYMBOLS_H_

#include <set>
#include "compiler/rules/symbol.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {

class SyntaxGrammar;

namespace build_tables {

/*
 *  Returns the set of symbols that can appear at the beginning of a sentential
 *  form derivable from a given rule in a given grammar.
 */
std::set<rules::Symbol> first_symbols(const rules::rule_ptr &rule,
                                      const SyntaxGrammar &grammar);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_FIRST_SYMBOLS_H_
