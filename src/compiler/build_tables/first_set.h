#ifndef COMPILER_BUILD_TABLES_FIRST_SET_H_
#define COMPILER_BUILD_TABLES_FIRST_SET_H_

#include <set>
#include "compiler/build_tables/parse_item.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

class SyntaxGrammar;

namespace build_tables {

/*
 *  Returns the set of terminal symbols that can appear at
 *  the beginning of a string derivable from a given rule,
 *  in a given grammar.
 */
std::set<rules::Symbol> first_set(const rules::rule_ptr &rule,
                                  const SyntaxGrammar &grammar);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_FIRST_SET_H_
