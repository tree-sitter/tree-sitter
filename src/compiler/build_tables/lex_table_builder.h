#ifndef COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <set>
#include "compiler/lex_table.h"

namespace tree_sitter {

struct ParseTable;
struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class LookaheadSet;

class LexTableBuilder {
 public:
  static std::unique_ptr<LexTableBuilder> create(const SyntaxGrammar &,
                                                 const LexicalGrammar &,
                                                 const std::unordered_map<rules::Symbol, LookaheadSet> &,
                                                 const std::vector<LookaheadSet> &);
  LexTable build(ParseTable *);
  const std::set<rules::Symbol> &get_incompatible_tokens(rules::Symbol::Index) const;

 protected:
  LexTableBuilder() = default;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_TABLE_BUILDER_H_
