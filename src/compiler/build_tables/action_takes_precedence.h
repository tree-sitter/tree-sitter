#ifndef COMPILER_BUILD_TABLES_RESOLVE_PARSE_ACTION_H_
#define COMPILER_BUILD_TABLES_RESOLVE_PARSE_ACTION_H_

#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/rules/symbol.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
namespace build_tables {

std::pair<bool, bool> action_takes_precedence(const ParseAction &new_action,
                                              const ParseAction &old_action,
                                              const rules::Symbol &symbol,
                                              const SyntaxGrammar &grammar);

bool action_takes_precedence(const LexAction &new_action,
                             const LexAction &old_action);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_RESOLVE_PARSE_ACTION_H_
