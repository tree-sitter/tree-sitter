#ifndef COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_

#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {

class LexAction;

namespace build_tables {

class LexConflictManager {
  const LexicalGrammar grammar;

 public:
  LexConflictManager(const LexicalGrammar &);
  bool resolve(const LexAction &, const LexAction &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
