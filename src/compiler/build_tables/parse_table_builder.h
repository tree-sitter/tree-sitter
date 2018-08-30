#ifndef COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_

#include <memory>
#include <unordered_map>
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
  static std::unique_ptr<ParseTableBuilder> create(
    const SyntaxGrammar &,
    const LexicalGrammar &,
    const std::unordered_map<rules::Symbol, rules::Alias> &
  );

  struct BuildResult {
    ParseTable parse_table;
    LexTable main_lex_table;
    LexTable keyword_lex_table;
    rules::Symbol keyword_capture_token;
    CompileError error;
  };

  BuildResult build();

 protected:
  ParseTableBuilder() = default;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_TABLE_BUILDER_H_
