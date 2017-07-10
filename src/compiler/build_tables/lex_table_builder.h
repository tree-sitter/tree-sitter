#ifndef COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_

#include <memory>
#include <vector>
#include <set>
#include "compiler/lex_table.h"

namespace tree_sitter {

struct ParseTable;
struct LexicalGrammar;

namespace build_tables {

class LexTableBuilder {
 public:
  static std::unique_ptr<LexTableBuilder> create(const LexicalGrammar &);
  LexTable build(ParseTable *);
  bool detect_conflict(
    rules::Symbol::Index,
    rules::Symbol::Index,
    const std::vector<std::set<rules::Symbol::Index>> &following_terminals_by_terminal_index
  );
 protected:
  LexTableBuilder() = default;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
