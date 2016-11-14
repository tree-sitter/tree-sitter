#ifndef COMPILER_BUILD_TABLES_DOES_MATCH_ANY_LINE_H_
#define COMPILER_BUILD_TABLES_DOES_MATCH_ANY_LINE_H_

#include "compiler/rule.h"
#include "compiler/rules/symbol.h"
#include <set>

namespace tree_sitter {

struct LexicalGrammar;

namespace build_tables {

std::set<rules::Symbol::Index> recovery_tokens(const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_DOES_MATCH_ANY_LINE_H_
