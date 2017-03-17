#ifndef COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_

#include <map>
#include <set>
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {

struct AdvanceAction;
struct AcceptTokenAction;

namespace build_tables {

class LexItemSet;

class LexConflictManager {
 public:
  bool resolve(const LexItemSet &, const AdvanceAction &,
               const AcceptTokenAction &);
  bool resolve(const AcceptTokenAction &, const AcceptTokenAction &);

  std::map<rules::Symbol::Index, std::set<rules::Symbol::Index>> possible_homonyms;
  std::map<rules::Symbol::Index, std::set<rules::Symbol::Index>> possible_extensions;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_CONFLICT_MANAGER_H_
