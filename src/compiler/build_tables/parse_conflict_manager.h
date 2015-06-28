#ifndef COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_

#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {

class ParseAction;
namespace rules { class Symbol; }

namespace build_tables {

enum ConflictType {
  ConflictTypeNone,
  ConflictTypeResolved,
  ConflictTypeUnresolved
};

class ParseConflictManager {
  const SyntaxGrammar syntax_grammar;

 public:
  ParseConflictManager(const SyntaxGrammar &);
  std::pair<bool, ConflictType> resolve(
    const ParseAction &, const ParseAction &, const rules::Symbol &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
