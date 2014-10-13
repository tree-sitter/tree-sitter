#ifndef COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_

#include <set>
#include <string>
#include <vector>
#include "compiler/parse_table.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/symbol.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

class ParseConflictManager {
  const SyntaxGrammar parse_grammar;
  const LexicalGrammar lex_grammar;
  std::set<Conflict> conflicts_;

 public:
  ParseConflictManager(const SyntaxGrammar &, const LexicalGrammar &);
  bool resolve_parse_action(const rules::Symbol &symbol,
                            const ParseAction &old_action,
                            const ParseAction &new_action);
  const std::vector<Conflict> conflicts() const;

 private:
  std::string symbol_name(const rules::Symbol &);
  void record_conflict(const rules::Symbol &, const ParseAction &,
                       const ParseAction &);
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
