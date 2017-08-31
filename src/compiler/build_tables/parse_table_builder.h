#ifndef COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_

#include <memory>
#include "compiler/parse_table.h"
#include "compiler/compile_error.h"

namespace tree_sitter {

struct ParseTable;
struct LexTable;
struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class ParseTableBuilder {
 public:
  static std::unique_ptr<ParseTableBuilder> create(const SyntaxGrammar &, const LexicalGrammar &);
  std::tuple<ParseTable, LexTable, CompileError> build();

 protected:
  ParseTableBuilder() = default;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_
