#ifndef COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_

#include <memory>
#include <vector>
#include <set>
#include "compiler/lex_table.h"

namespace tree_sitter {

struct ParseTable;
struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class LexTableBuilder {
 public:
  static std::unique_ptr<LexTableBuilder> create(const SyntaxGrammar &,
                                                 const LexicalGrammar &,
                                                 const std::vector<std::set<rules::Symbol::Index>> &);
  LexTable build(ParseTable *);
  const std::set<rules::Symbol> &get_incompatible_tokens(rules::Symbol::Index) const;

 protected:
  LexTableBuilder() = default;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
